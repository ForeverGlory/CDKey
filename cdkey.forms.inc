<?php

function cdkey_use_form($form, &$form_state, $cdkey_type, $cdkey = NULL) {
  $form['#cdkey_type'] = $cdkey_type;
  $form['#cdkey'] = $cdkey;
  $form['sn'] = array(
    '#title' => t('CDKey SN'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => isset($cdkey->sn) ? $cdkey->sn : '',
    '#weight' => 0,
  );
  $form['pass'] = array(
    '#title' => t('CDKey password'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#default_value' => '',
    '#weight' => 1,
  );
  $cdkey_use = entity_create('cdkey_use', array('sn' => isset($cdkey->sn) ? $cdkey->sn : '', 'type' => isset($cdkey_type->type) ? $cdkey_type->type : ''));

  field_attach_form('cdkey_use', $cdkey_use, $form, $form_state);

  $form['actions'] = array(
    '#weight' => 100,
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('CDKey Verify'),
  );
  $form['#validate'][] = 'cdkey_use_form_validate';
  $form['#submit'][] = 'cdkey_use_form_submit';
  return $form;
}

function cdkey_use_form_validate($form, &$form_state) {
  if (empty($form_state['values']['sn'])) {
    form_set_error('sn', t('Please input CDKey serial-number.'));
  } elseif (empty($form_state['values']['pass'])) {
    form_set_error('pass', t('Please input CDKey password.'));
  } else {
    $cdkey = cdkey_load_by_sn($form_state['values']['sn'], $form_state['values']['pass']);
    if (empty($cdkey)) {
      form_set_error('pass', t('CDKey is error.'));
    } else {
      $form_state['cdkey'] = $cdkey;
      if (cdkey_is_useble($cdkey)) {
        $form_state['cdkey_use'] = cdkey_use_create($cdkey);
      } else {
        form_set_error('sn', t('CDKey is used'));
      }
    }
  }
}

function cdkey_use_form_submit($form, &$form_state) {
  $cdkey = $form_state['cdkey'];
  $cdkey_use = $form_state['cdkey_use'];
  entity_form_submit_build_entity('cdkey_use', $cdkey_use, $form, $form_state);
  cdkey_use_save($cdkey_use);
  $form_state['redirect'] = 'cdkey/confirm/' . $cdkey->sn;
}

function cdkey_confirm_form($form, &$form_state, $cdkey) {
  $form['#cdkey'] = $cdkey;
  $form['#cdkey_use'] = cdkey_use_create($cdkey);
  $cdkey_view = entity_view('cdkey', array(entity_id('cdkey', $cdkey) => $cdkey), 'use');
  $form['cdkey'] = array(
    '#markup' => render($cdkey_view)
  );
  $form['actions'] = array(
    '#weight' => 100,
  );
  $form['actions']['confirm'] = array(
    '#type' => 'submit',
    '#value' => t('CDKey confirm')
  );
  $form['#validate'][] = 'cdkey_confirm_form_validate';
  $form['#submit'][] = 'cdkey_confirm_form_submit';
  return $form;
}

function cdkey_confirm_form_validate($form, &$form_state) {
  
}

function cdkey_confirm_form_submit($form, &$form_state) {
  $cdkey = $form['#cdkey'];
  $cdkey_use = $form['#cdkey_use'];
  cdkey_use_save($cdkey_use);
  $form_state['redirect'] = 'cdkey/' . $cdkey->sn;
}
