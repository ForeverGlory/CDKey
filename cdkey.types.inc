<?php

function cdkey_overview_types() {
  $types = cdkey_type_get_types();
  $names = cdkey_type_get_names();
  $field_ui = module_exists('field_ui');
  $header = array(t('Name'), array('data' => t('Operations'), 'colspan' => $field_ui ? '4' : '2'));
  $rows = array();

  foreach ($names as $key => $name) {
    $type = $types[$key];
    $type_url_str = str_replace('_', '-', $type->type);
    $row = array(theme('cdkey_admin_overview', array('name' => $name, 'type' => $type)));
    // Set the edit column.
    $row[] = array('data' => l(t('edit'), 'admin/structure/cdkey/manage/' . $type_url_str));

    if ($field_ui) {
      // Manage fields.
      $row[] = array('data' => l(t('manage fields'), 'admin/structure/cdkey/manage/' . $type_url_str . '/fields'));

      // Display fields.
      $row[] = array('data' => l(t('manage display'), 'admin/structure/cdkey/manage/' . $type_url_str . '/display'));
    }
    //删除，可增加自定义
    if (TRUE) {
      $row[] = array('data' => l(t('delete'), 'admin/structure/cdkey/manage/' . $type_url_str . '/delete'));
    } else {
      $row[] = array();
    }
    $rows[] = $row;
  }

  $build['cdkey_table'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('No CDKEY types available. <a href="@link">Add CDKEY type</a>.', array('@link' => url('admin/structure/cdkey/add'))),
  );

  return $build;
}

function cdkey_type_form($form, &$form_state, $type = Null) {
  $form_state['cdkey_type'] = $type;
  $op = isset($type) ? 'edit' : 'add';
  $form['name'] = array(
    '#title' => t('name'),
    '#type' => 'textfield',
    '#default_value' => $op == 'edit' ? $type->name : '',
    '#description' => t('The human-readable name of this entity type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => $op == 'edit' ? $type->type : '',
    '#maxlength' => 32,
    '#disabled' => $op == 'edit',
    '#machine_name' => array(
      'exists' => 'cdkey_type_load',
      'source' => array('name'),
      'replace' => '-',
    ),
    '#description' => t('A unique machine-readable name for this entity type. It must only contain lowercase letters, numbers, and underscores.'),
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#default_value' => $op == 'edit' ? $type->description : '',
    '#description' => t('Description about the entity type.'),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#weight' => 40,
    '#submit' => array('cdkey_type_form_submit')
  );
  if ($op == 'edit') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('cdkey_type_form_delete'),
    );
  }

  return $form;
}

/**
 * Entity type edit form "Save" submit handler.
 */
function cdkey_type_form_submit($form, &$form_state) {
  $values = array(
    'type' => $form_state['values']['type'],
    'name' => $form_state['values']['name'],
    'description' => $form_state['values']['description']
  );
  $type = cdkey_type_set_defaults($values);
  cdkey_type_save($type);
  drupal_set_message(t('@type %name has been created.', array('@type' => $type->type, '%name' => $type->name)));
  // Redirect user.
  $form_state['redirect'] = 'admin/structure/cdkey';
}

/**
 * Entity type edit form "Delete" submit handler.
 */
function cdkey_type_form_delete(&$form, &$form_state) {
  // Redirect user to "Delete" URI for this entity type.
  $form_state['redirect'] = 'admin/structure/cdkey/manage/' . $form_state['cdkey_type']->type . '/delete';
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
function cdkey_type_form_delete_confirm($form, &$form_state, $type) {
  $form_state['cdkey_type'] = $type;
  $message = t('Are you sure you want to delete CDKEY type %name?', array('%name' => $type->name));
  return confirm_form(
          $form, $message, 'admin/structure/cdkey/manage/' . $type->type, t('This action cannot be undone.'), t('Delete'), t('Cancel')
  );
}

/**
 * Entity type "Confirm delete" form submit handler.
 */
function cdkey_type_form_delete_confirm_submit($form, &$form_state) {
  // Delete the entity type.
  $type = $form_state['cdkey_type'];
  cdkey_type_delete($type);
  // Redirect user.
  drupal_set_message(t('@type %name has been deleted.', array('@type' => $type->type, '%name' => $type->name)));
  $form_state['redirect'] = 'admin/structure/cdkey';
}

/**
 * Returns HTML for a node type description for the content type admin overview page.
 *
 * @param $variables
 *   An associative array containing:
 *   - name: The human-readable name of the content type.
 *   - type: An object containing the 'type' (machine name) and 'description' of
 *     the content type.
 *
 * @ingroup themeable
 */
function theme_cdkey_admin_overview($variables) {
  $name = $variables['name'];
  $type = $variables['type'];

  $output = check_plain($name);
  $output .= ' <small>' . t('(Machine name: @type)', array('@type' => $type->type)) . '</small>';
  $output .= '<div class="description">' . filter_xss_admin($type->description) . '</div>';
  return $output;
}