<?php

function cdkey_admin_page($form, $form_state) {
  if (isset($form_state['values']['operation']) && $form_state['values']['operation'] == 'delete') {
    return node_multiple_delete_confirm($form, $form_state, array_filter($form_state['values']['nodes']));
  }
  $form['filter'] = cdkey_filter_form();
  $form['#submit'][] = 'node_filter_form_submit';
  $form['admin'] = cdkey_admin_list();

  return $form;
}

function cdkey_filter_form() {
  $session = isset($_SESSION['node_overview_filter']) ? $_SESSION['node_overview_filter'] : array();
  $filters = cdkey_filters();

  $i = 0;
  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Show only items where'),
    '#theme' => 'exposed_filters__node',
  );
  foreach ($session as $filter) {
    list($type, $value) = $filter;
    if ($type == 'term') {
      // Load term name from DB rather than search and parse options array.
      $value = module_invoke('taxonomy', 'term_load', $value);
      $value = $value->name;
    } elseif ($type == 'language') {
      $value = $value == LANGUAGE_NONE ? t('Language neutral') : module_invoke('locale', 'language_name', $value);
    } else {
      $value = $filters[$type]['options'][$value];
    }
    $t_args = array('%property' => $filters[$type]['title'], '%value' => $value);
    if ($i++) {
      $form['filters']['current'][] = array('#markup' => t('and where %property is %value', $t_args));
    } else {
      $form['filters']['current'][] = array('#markup' => t('where %property is %value', $t_args));
    }
    if (in_array($type, array('type', 'language'))) {
      // Remove the option if it is already being filtered on.
      unset($filters[$type]);
    }
  }

  $form['filters']['status'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('clearfix')),
    '#prefix' => ($i ? '<div class="additional-filters">' . t('and where') . '</div>' : ''),
  );
  $form['filters']['status']['filters'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('filters')),
  );
  foreach ($filters as $key => $filter) {
    $form['filters']['status']['filters'][$key] = array(
      '#type' => 'select',
      '#options' => $filter['options'],
      '#title' => $filter['title'],
      '#default_value' => '[any]',
    );
  }

  $form['filters']['status']['actions'] = array(
    '#type' => 'actions',
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['filters']['status']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => count($session) ? t('Refine') : t('Filter'),
  );
  if (count($session)) {
    $form['filters']['status']['actions']['undo'] = array('#type' => 'submit', '#value' => t('Undo'));
    $form['filters']['status']['actions']['reset'] = array('#type' => 'submit', '#value' => t('Reset'));
  }

  drupal_add_js('misc/form.js');

  return $form;
}

function cdkey_filters() {
  $filters['type'] = array(
    'title' => t('type'),
    'options' => array(
  '[any]' => t('any'),
    ) + cdkey_type_get_names(),
  );
  return $filters;
}

function cdkey_admin_list() {
  $admin_access = user_access('administer nodes');

  // Build the 'Update options' form.
  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Update options'),
    '#attributes' => array('class' => array('container-inline')),
    '#access' => $admin_access,
  );
  $options = array();
  foreach (module_invoke_all('node_operations') as $operation => $array) {
    $options[$operation] = $array['label'];
  }
  $form['options']['operation'] = array(
    '#type' => 'select',
    '#title' => t('Operation'),
    '#title_display' => 'invisible',
    '#options' => $options,
    '#default_value' => 'approve',
  );
  $form['options']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
    '#validate' => array('node_admin_nodes_validate'),
    '#submit' => array('node_admin_nodes_submit'),
  );

  // Enable language column if translation module is enabled or if we have any
  // node with language.
  $multilanguage = (module_exists('translation') || db_query_range("SELECT 1 FROM {node} WHERE language <> :language", 0, 1, array(':language' => LANGUAGE_NONE))->fetchField());

  // Build the sortable table header.
  $header = array(
    'title' => array('data' => t('Title'), 'field' => 'n.title'),
    'type' => array('data' => t('Type'), 'field' => 'n.type'),
    'author' => t('Author'),
    'status' => array('data' => t('Status'), 'field' => 'n.status'),
    'changed' => array('data' => t('Updated'), 'field' => 'n.changed', 'sort' => 'desc')
  );
  if ($multilanguage) {
    $header['language'] = array('data' => t('Language'), 'field' => 'n.language');
  }
  $header['operations'] = array('data' => t('Operations'));

  $query = db_select('node', 'n')->extend('PagerDefault')->extend('TableSort');
  //node_build_filter_query($query);

  if (!user_access('bypass node access')) {
    // If the user is able to view their own unpublished nodes, allow them
    // to see these in addition to published nodes. Check that they actually
    // have some unpublished nodes to view before adding the condition.
    if (user_access('view own unpublished content') && $own_unpublished = db_query('SELECT nid FROM {node} WHERE uid = :uid AND status = :status', array(':uid' => $GLOBALS['user']->uid, ':status' => 0))->fetchCol()) {
      $query->condition(db_or()
              ->condition('n.status', 1)
              ->condition('n.nid', $own_unpublished, 'IN')
      );
    } else {
      // If not, restrict the query to published nodes.
      $query->condition('n.status', 1);
    }
  }
  $nids = $query
      ->fields('n', array('nid'))
      ->limit(50)
      ->orderByHeader($header)
      ->addTag('node_access')
      ->execute()
      ->fetchCol();
  $nodes = node_load_multiple($nids);

  // Prepare the list of nodes.
  $languages = language_list();
  $destination = drupal_get_destination();
  $options = array();
  foreach ($nodes as $node) {
    $langcode = entity_language('node', $node);
    $l_options = $langcode != LANGUAGE_NONE && isset($languages[$langcode]) ? array('language' => $languages[$langcode]) : array();
    $options[$node->nid] = array(
      'title' => array(
        'data' => array(
          '#type' => 'link',
          '#title' => $node->title,
          '#href' => 'node/' . $node->nid,
          '#options' => $l_options,
          '#suffix' => ' ' . theme('mark', array('type' => node_mark($node->nid, $node->changed))),
        ),
      ),
      'type' => check_plain(node_type_get_name($node)),
      'author' => theme('username', array('account' => $node)),
      'status' => $node->status ? t('published') : t('not published'),
      'changed' => format_date($node->changed, 'short'),
    );
    if ($multilanguage) {
      if ($langcode == LANGUAGE_NONE || isset($languages[$langcode])) {
        $options[$node->nid]['language'] = $langcode == LANGUAGE_NONE ? t('Language neutral') : t($languages[$langcode]->name);
      } else {
        $options[$node->nid]['language'] = t('Undefined language (@langcode)', array('@langcode' => $langcode));
      }
    }
    // Build a list of all the accessible operations for the current node.
    $operations = array();
    if (node_access('update', $node)) {
      $operations['edit'] = array(
        'title' => t('edit'),
        'href' => 'node/' . $node->nid . '/edit',
        'query' => $destination,
      );
    }
    if (node_access('delete', $node)) {
      $operations['delete'] = array(
        'title' => t('delete'),
        'href' => 'node/' . $node->nid . '/delete',
        'query' => $destination,
      );
    }
    $options[$node->nid]['operations'] = array();
    if (count($operations) > 1) {
      // Render an unordered list of operations links.
      $options[$node->nid]['operations'] = array(
        'data' => array(
          '#theme' => 'links__node_operations',
          '#links' => $operations,
          '#attributes' => array('class' => array('links', 'inline')),
        ),
      );
    } elseif (!empty($operations)) {
      // Render the first and only operation as a link.
      $link = reset($operations);
      $options[$node->nid]['operations'] = array(
        'data' => array(
          '#type' => 'link',
          '#title' => $link['title'],
          '#href' => $link['href'],
          '#options' => array('query' => $link['query']),
        ),
      );
    }
  }

  // Only use a tableselect when the current user is able to perform any
  // operations.
  if ($admin_access) {
    $form['nodes'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#empty' => t('No content available.'),
    );
  }
  // Otherwise, use a simple table.
  else {
    $form['nodes'] = array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $options,
      '#empty' => t('No content available.'),
    );
  }

  $form['pager'] = array('#markup' => theme('pager'));
  return $form;
}

/**
 * Choose bundle of entity to add.
 * 
 * @return array
 *   Array describing a list of bundles to render.
 */
function cdkey_choose_bundle() {
  // Show list of all existing entity bundles.
  $items = array();
  foreach (cdkey_type_load_multiple() as $entity_type_key => $entity_type) {
    $items[] = l(entity_label('cdkey_type', $entity_type), 'admin/cdkey/add/' . $entity_type_key);
  }
  return array(
    'list' => array(
      '#theme' => 'item_list',
      '#items' => $items,
      '#title' => t('Choose type of entity to add.'),
    ),
  );
}

/**
 * Form constructor for the entity add form.
 * 
 * @param string $type
 *   Entity type (bundle) to add.
 * 
 * @return array
 *   Entity edit form.
 */
function cdkey_add($type) {
  $entity_type = cdkey_type_load_multiple($type);
  drupal_set_title(t('Create @name', array('@name' => entity_label('entity_type', $entity_type))));

  // Return form for the given entity bundle.
  $entity = entity_create('cdkey', array('type' => $type));
  return drupal_get_form('cdkey_add_form', $type, $entity);
}

/**
 * Form constructor for the entity edit form.
 * 
 * In this form we shall manually define all form elements related to editable
 * properties of the entity.
 * 
 * @param object $entity
 *   Entity to edit.
 * 
 * @return array
 *   Entity edit form.
 */
function cdkey_add_form($form, &$form_state, $type = '', $entity = NULL) {
  // Store the entity in the form.
  $form_state['entity'] = $entity;

  // Describe all properties of the entity which shall be shown on the form.
  $wrapper = entity_metadata_wrapper('cdkey', $entity);

  $form['type'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t('CDKey Type'),
    '#default_value' => $type
  );

  $form['sn'] = array(
    '#type' => 'textfield',
    '#required' => FALSE,
    '#title' => t('CDKey SN'),
      //'#default_value' => $wrapper->cdkey->sn,
  );
  $form['keyt'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('CDKey Key'),
      //'#default_value' => $wrapper->cdkey->key,
  );

  // Add fields of the entity to the form.
  field_attach_form('cdkey', $entity, $form, $form_state);

  // Add some buttons.
  $submit = array();
  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }
  $form['actions'] = array(
    '#weight' => 100,
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save CDKey'),
    '#submit' => $submit + array('cdkey_form_submit'),
  );
  $entity_id = entity_id('cdkey', $entity);

  if (!empty($entity_id)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('cdkey_form_submit_delete'),
    );
  }

  return $form;
}

/**
 * Entity edit form "Save" submit handler.
 */
function cdkey_form_submit($form, &$form_state) {
  // Automatically get edited entity from the form and save it.
  // @see entity_form_submit_build_entity()
  $entity = $form_state['entity'];

  entity_form_submit_build_entity('cdkey', $entity, $form, $form_state);
  cdkey_save($entity);
  // Redirect user to edited entity page.
  $entity_uri = entity_uri('cdkey', $entity);
  //$form_state['redirect'] = $entity_uri['path'];
  drupal_set_message(t('CDKey %title saved.', array('%title' => entity_label('cdkey', $entity))));
}

/**
 * Entity edit form "Delete" submit handler.
 */
function cdkey_form_submit_delete($form, &$form_state) {
  // Redirect user to "Delete" URI for this entity.
  $entity = $form_state['entity'];
  $entity_uri = entity_uri('cdkey', $entity);
  $form_state['redirect'] = $entity_uri['path'] . '/delete';
}

/**
 * Form constructor for the entity delete confirmation form.
 * 
 * @param object $entity
 *   Entity to delete.
 * 
 * @return array
 *   Confirmation form.
 */
function cdkey_delete_form($form, &$form_state, $entity) {
  // Store the entity in the form.
  $form_state['entity'] = $entity;

  // Show confirm dialog.
  $entity_uri = entity_uri('cdkey', $entity);
  $message = t('Are you sure you want to delete cdkey %title?', array('%title' => entity_label('cdkey', $entity)));
  return confirm_form(
      $form, $message, $entity_uri['path'], t('This action cannot be undone.'), t('Delete'), t('Cancel')
  );
}

/**
 * Entity "Confirm delete" form submit handler.
 */
function cdkey_delete_form_submit($form, &$form_state) {
  // Delete the entity.
  $entity = $form_state['entity'];
  entity_delete('cdkey', entity_id('cdkey', $entity));

  // Redirect user.
  drupal_set_message(t('CDKey %title deleted.', array('%title' => entity_label('cdkey', $entity))));
  $form_state['redirect'] = '<front>';
}

function cdkey_generate($type) {
  return drupal_get_form('cdkey_generate_form', $type);
}

function cdkey_generate_form($form, &$form_state, $type = '') {
  return $form;
}

/**
 * Form constructor for the entity type edit form.
 * 
 * In this form we shall manually define all form elements related to editable
 * properties of the entity.
 * 
 * @param object $entity_type
 *   Enity type.
 * @param string $op
 *   Operation to perform on entity type.
 * 
 * @return array
 *   Entity type edit form.
 */
function cdkey_type_form($form, &$form_state, $entity_type, $op = 'edit') {
  // Handle the case when cloning is performed.
  if ($op == 'clone') {
    $entity_type->label .= ' (cloned)';
    $entity_type->type = '';
  }

  // Describe all properties of the entity which shall be shown on the form.
  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $entity_type->label,
    '#description' => t('The human-readable name of this entity type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($entity_type->type) ? $entity_type->type : '',
    '#maxlength' => 32,
    '#disabled' => $entity_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'cdkey_type_load_multiple',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this entity type. It must only contain lowercase letters, numbers, and underscores.'),
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#default_value' => isset($entity_type->description) ? $entity_type->description : '',
    '#description' => t('Description about the entity type.'),
  );

  // Add some buttons.
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save entity type'),
    '#weight' => 40,
  );
  if (!$entity_type->isLocked() && $op != 'add' && $op != 'clone') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete entity type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('cdkey_type_form_submit_delete'),
    );
  }

  return $form;
}

/**
 * Entity type edit form "Save" submit handler.
 */
function cdkey_type_form_submit(&$form, &$form_state) {
  // Automatically get edited entity type from the form and save it.
  // @see entity_ui_form_submit_build_entity()
  $entity_type = entity_ui_form_submit_build_entity($form, $form_state);
  cdkey_type_save($entity_type);
  // Redirect user.
  $form_state['redirect'] = 'admin/structure/cdkey';
}

/**
 * Entity edit form "Delete" submit handler.
 */
function cdkey_type_form_submit_delete(&$form, &$form_state) {
  // Redirect user to "Delete" URI for this entity type.
  $form_state['redirect'] = 'admin/structure/cdkey/' . $form_state['cdkey_type']->type . '/delete';
}

/**
 * Form constructor for the entity type delete confirmation form.
 * 
 * @param object $entity_type
 *   Entity type to delete.
 * 
 * @return array
 *   Confirmation form.
 */
function cdkey_type_form_delete_confirm($form, &$form_state, $entity_type) {
  // Store the entity in the form.
  $form_state['entity_type'] = $entity_type;

  // Show confirm dialog.
  $message = t('Are you sure you want to delete entity type %title?', array('%title' => entity_label('entity_type', $entity_type)));
  return confirm_form(
      $form, $message, 'admin/cdkey/' . entity_id('cdkey_type', $entity_type), t('This action cannot be undone.'), t('Delete'), t('Cancel')
  );
}

/**
 * Entity type "Confirm delete" form submit handler.
 */
function cdkey_type_form_delete_confirm_submit($form, &$form_state) {
  // Delete the entity type.
  $entity_type = $form_state['entity_type'];
  entity_delete('cdkey_type', entity_id('cdkey_type', $entity_type));

  // Redirect user.
  drupal_set_message(t('@type %title has been deleted.', array('@type' => $entity_type->type, '%title' => $entity_type->label)));
  $form_state['redirect'] = 'admin/structure/cdkey';
}
