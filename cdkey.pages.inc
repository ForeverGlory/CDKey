<?php

function cdkey_use_page($cdkey_type = NULL, $cdkey = NULL) {
  if ($cdkey_type == NULL && $cdkey == NULL) {
    return MENU_NOT_FOUND;
  } elseif (!is_object($cdkey_type)) {
    $cdkey_type = cdkey_type_load($cdkey_type);
  }
  if ($cdkey == NULL) {
    $cdkey = entity_create('cdkey', array('type' => $cdkey_type->type));
  } elseif (!is_object($cdkey)) {
    $cdkey = cdkey_load_by_sn($cdkey);
    if (empty($cdkey)) {
      return MENU_NOT_FOUND;
    }
  }
  $form = drupal_get_form('cdkey_use_form', $cdkey_type, $cdkey);
  return theme('cdkey_use', array('cdkey_type' => $cdkey_type, 'cdkey' => $cdkey, 'cdkey_use_form' => $form));
}

function cdkey_confirm_page($cdkey = NULL) {
  return drupal_get_form('cdkey_confirm_form', $cdkey);
}
