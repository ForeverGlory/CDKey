<?php

function cdkey_add_page() {
  $item = menu_get_item();
  if ($content = system_admin_menu_block($item)) {
    $output = theme('admin_block_content', array('content' => $content));
  } else {
    $output = t('You haven\'t add any CDKey type');
  }
  return $output;
}

/**
 * Add / Edit CDKey from
 */
function cdkey_form($form, &$form_state, $cdkey_type = NULL, $cdkey = NULL) {
  if ($cdkey_type == NULL && $cdkey == NULL) {
    drupal_set_message(t('CDKey or CDKey type does not exist'), 'error');
    return array();
  }
  if ($cdkey == NULL) {
    $cdkey = entity_create('cdkey', array('type' => $cdkey_type));
    $cdkey_type = cdkey_type_load($cdkey_type);
  } else {
    $cdkey_type = cdkey_type_load($cdkey->type);
  }
  //$wrapper = entity_metadata_wrapper('cdkey', $cdkey);
  //将 $cdkey, $cdkey_type 存储于表单中
  $form['#cdkey'] = $cdkey;
  $form['#cdkey_type'] = $cdkey_type;

  $form['sn'] = array(
    '#type' => 'textfield',
    '#required' => FALSE,
    '#title' => t('CDKey serial-number'),
    '#default_value' => isset($cdkey->sn) ? $cdkey->sn : '',
    '#weigth' => -5,
  );
  $form['pass'] = array(
    '#type' => 'textfield',
    '#required' => TRUE,
    '#title' => t('CDKey password'),
    '#default_value' => isset($cdkey->pass) ? $cdkey->pass : '',
    '#weigth' => -4,
  );

  // Add fields of the entity to the form.
  field_attach_form('cdkey', $cdkey, $form, $form_state);

  $form['actions'] = array(
    '#weight' => 100,
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save CDKey'),
    '#submit' => array('cdkey_form_submit'),
  );
  if (entity_id('cdkey', $cdkey)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('cdkey_form_submit_delete'),
    );
  }

  return $form;
}

/**
 * Save CDKey, update/create
 */
function cdkey_form_submit($form, &$form_state) {
  $cdkey = $form['#cdkey'];
  entity_form_submit_build_entity('cdkey', $cdkey, $form, $form_state);
  $save_status = cdkey_save($cdkey);
  if ($save_status == SAVED_NEW) {
    watchdog('cdkey', '@type @sn saved for new.', array('@type' => $cdkey->type, '@sn' => $cdkey->sn));
  } elseif ($save_status == SAVED_UPDATED) {
    watchdog('cdkey', '@type @sn saved for update.', array('@type' => $cdkey->type, '@sn' => $cdkey->sn));
  }
  drupal_set_message(t('CDKey %sn saved.', array('%sn' => entity_label('cdkey', $cdkey))));
}

/**
 * go to delete uri
 */
function cdkey_form_submit_delete($form, &$form_state) {
  // Redirect user to "Delete" URI for this entity.
  $form_state['redirect'] = 'admin/cdkey/' . entity_id('cdkey', $form['#cdkey']) . '/delete';
}

/**
 * Delete CDKey Form
 */
function cdkey_delete_form($form, &$form_state, $cdkey) {
  $form['#cdkey'] = $cdkey;
  $message = t('Are you sure you want to delete CDKey %sn?', array('%sn' => entity_label('cdkey', $cdkey)));
  return confirm_form(
          $form, $message, 'admin/cdkey/' . entity_id('cdkey', $cdkey), t('This action cannot be undone.'), t('Delete'), t('Cancel')
  );
}

/**
 * Delete CDKey
 */
function cdkey_delete_form_submit($form, &$form_state) {
  // Delete the entity.
  $cdkey = $form['#cdkey'];
  entity_delete('cdkey', entity_id('cdkey', $cdkey));
  watchdog('cdkey', 'type @type, sn @sn deleted.', array('@type' => $cdkey->type, '@sn' => $cdkey->sn));
  drupal_set_message(t('CDKey %sn deleted.', array('%sn' => entity_label('cdkey', $cdkey))));
  // Redirect user.
  $form_state['redirect'] = 'admin/cdkey';
}
