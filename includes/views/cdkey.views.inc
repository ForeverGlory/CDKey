<?php

/**
 * Implements hook_views_data().
 */
function cdkey_views_data() {
  $data = array();
  $data['views_entity_cdkey']['table']['group'] = t('CDKey');

  $data['cdkey']['edit']['moved to'] = array('views_entity_cdkey', 'edit');
  $data['views_entity_cdkey']['edit'] = array(
    'field' => array(
      'title' => t('Edit'),
      'help' => t('CDKey Edit Uri'),
      'handler' => 'cdkey_handler_field_cdkey_edit',
    ),
  );

  $data['cdkey']['delete']['moved to'] = array('views_entity_cdkey', 'delete');
  $data['views_entity_cdkey']['delete'] = array(
    'field' => array(
      'title' => t('Delete'),
      'help' => t('CDKey Delete Uri'),
      'handler' => 'cdkey_handler_field_cdkey_delete',
    ),
  );

  return $data;
}
