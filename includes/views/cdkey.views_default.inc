<?php

/**
 * Implements hook_views_default_views().
 */
function cdkey_views_default_views() {
  $views['cdkey'] = _cdkey_views();
  $views['cdkey_use'] = _cdkey_used_views();
  return $views;
}

function _cdkey_views() {
  $view = new view();
  $view->name = 'cdkey';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'cdkey';
  $view->human_name = 'CDKey';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'CDKey';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'more';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view cdkey_entity content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'search';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'reset';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'sort';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'asc';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'desc';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = '每页条目数';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- All -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = '偏移量';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« 第一页';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ 前一页';
  $handler->display->display_options['pager']['options']['tags']['next'] = '下一页 ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = '末页 »';
  $handler->display->display_options['style_plugin'] = 'table';
  /* 头部: 全局: 文本域 */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<a href="<?php print url(\'admin/cdkey/add\'); ?>>Add CDKey</a>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* 关联: 标示: cdkey_used 计数 */
  $handler->display->display_options['relationships']['flag_count_rel']['id'] = 'flag_count_rel';
  $handler->display->display_options['relationships']['flag_count_rel']['table'] = 'cdkey';
  $handler->display->display_options['relationships']['flag_count_rel']['field'] = 'flag_count_rel';
  $handler->display->display_options['relationships']['flag_count_rel']['label'] = 'Used Num';
  $handler->display->display_options['relationships']['flag_count_rel']['required'] = 0;
  $handler->display->display_options['relationships']['flag_count_rel']['flag'] = 'cdkey_used';
  /* 字段: 批量操作: 代码 */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'cdkey';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_revision' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* 字段: 代码: CDKey Type (bundle) */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'cdkey';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = 'CDKey Type';
  /* 字段: 代码: CDKey SN */
  $handler->display->display_options['fields']['sn']['id'] = 'sn';
  $handler->display->display_options['fields']['sn']['table'] = 'cdkey';
  $handler->display->display_options['fields']['sn']['field'] = 'sn';
  /* 字段: 代码: CDKey Key */
  $handler->display->display_options['fields']['keyt']['id'] = 'keyt';
  $handler->display->display_options['fields']['keyt']['table'] = 'cdkey';
  $handler->display->display_options['fields']['keyt']['field'] = 'keyt';
  /* 字段: 代码: CDKey Expire */
  $handler->display->display_options['fields']['expire']['id'] = 'expire';
  $handler->display->display_options['fields']['expire']['table'] = 'cdkey';
  $handler->display->display_options['fields']['expire']['field'] = 'expire';
  /* 字段: 代码: CDKey Num */
  $handler->display->display_options['fields']['num']['id'] = 'num';
  $handler->display->display_options['fields']['num']['table'] = 'cdkey';
  $handler->display->display_options['fields']['num']['field'] = 'num';
  /* 字段: 标示: 标示计数 */
  $handler->display->display_options['fields']['count']['id'] = 'count';
  $handler->display->display_options['fields']['count']['table'] = 'flag_counts';
  $handler->display->display_options['fields']['count']['field'] = 'count';
  $handler->display->display_options['fields']['count']['relationship'] = 'flag_count_rel';
  $handler->display->display_options['fields']['count']['label'] = 'Used Num';
  /* 字段: 代码: CDKey Create Time */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'cdkey';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  /* 字段: 代码: CDKey Create UserId */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'cdkey';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = 'CDKey Create User';
  /* 字段: 代码: CDKey Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'cdkey';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* 字段: 全局: 定制文本 */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '操作';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '编辑';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'admin/cdkey/[sn]/edit';
  /* 过滤规则: 代码: CDKey Key */
  $handler->display->display_options['filters']['keyt']['id'] = 'keyt';
  $handler->display->display_options['filters']['keyt']['table'] = 'cdkey';
  $handler->display->display_options['filters']['keyt']['field'] = 'keyt';
  $handler->display->display_options['filters']['keyt']['operator'] = 'contains';
  $handler->display->display_options['filters']['keyt']['group'] = 1;
  $handler->display->display_options['filters']['keyt']['exposed'] = TRUE;
  $handler->display->display_options['filters']['keyt']['expose']['operator_id'] = 'keyt_op';
  $handler->display->display_options['filters']['keyt']['expose']['label'] = 'CDKey Key';
  $handler->display->display_options['filters']['keyt']['expose']['operator'] = 'keyt_op';
  $handler->display->display_options['filters']['keyt']['expose']['identifier'] = 'keyt';
  $handler->display->display_options['filters']['keyt']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* 过滤规则: 代码: CDKey Type (bundle) */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'cdkey';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'CDKey Type (bundle)';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['type']['group_info']['label'] = 'CDKey Type';
  $handler->display->display_options['filters']['type']['group_info']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Product Register CDKey',
      'operator' => '=',
      'value' => 'product_register',
    ),
    2 => array(
      'title' => '',
      'operator' => '=',
      'value' => '',
    ),
    3 => array(
      'title' => '',
      'operator' => '=',
      'value' => '',
    ),
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/cdkey';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'CDKey';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['cdkey'] = array(
    t('Master'),
    t('代码'),
    t('更多'),
    t('搜索'),
    t('重置'),
    t('排序依据'),
    t('升序'),
    t('降序'),
    t('每页条目数'),
    t('- 全部 -'),
    t('偏移量'),
    t('« 第一页'),
    t('‹ 前一页'),
    t('下一页 ›'),
    t('末页 »'),
    t('<a href="<?php print url(\'admin/cdkey/add\'); ?>>Add CDKey</a>'),
    t('Used Num'),
    t('- 选择一个操作 -'),
    t('CDKey Type'),
    t('CDKey SN'),
    t('CDKey Key'),
    t('CDKey Expire'),
    t('.'),
    t(','),
    t('CDKey Num'),
    t('CDKey Create Time'),
    t('CDKey Create User'),
    t('CDKey Status'),
    t('操作'),
    t('编辑'),
    t('CDKey Type (bundle)'),
    t('Page'),
  );
  return $view;
}

function _cdkey_used_views() {
  $view = new view();
  $view->name = 'cdkey_used';
  $view->description = 'CDKey Used';
  $view->tag = 'flag';
  $view->base_table = 'cdkey';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'CDKey Used';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = '更多';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer flags';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = '搜索';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = '重置';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = '排序依据';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = '升序';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = '降序';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = '';
  $handler->display->display_options['style_options']['columns'] = array(
    'cdkey' => 'cdkey',
    'user' => 'user',
  );
  $handler->display->display_options['style_options']['default'] = 'last_comment_timestamp';
  $handler->display->display_options['style_options']['info'] = array(
    'cdkey' => array(
      'sortable' => TRUE,
    ),
  );
  $handler->display->display_options['style_options']['override'] = FALSE;
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['order'] = 'desc';
  /* 关联: 标示: cdkey_used */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'cdkey';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'cdkey_used';
  $handler->display->display_options['relationships']['flag_content_rel']['user_scope'] = 'any';
  /* 关联: 标示: 用户 */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'flagging';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* 字段: 代码: CDKey Key */
  $handler->display->display_options['fields']['cdkey']['id'] = 'cdkey';
  $handler->display->display_options['fields']['cdkey']['table'] = 'cdkey';
  $handler->display->display_options['fields']['cdkey']['field'] = 'cdkey';
  $handler->display->display_options['fields']['cdkey']['label'] = 'CDKey';
  /* 字段: 代码: CDKey Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'cdkey';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* 字段: 代码: CDKey Type (bundle) */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'cdkey';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* 字段: 标示: 标示时间 */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'flagging';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'Y-m-d H:i:s';
  /* 字段: 用户: 名字 */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* 过滤规则: 代码: CDKey Key */
  $handler->display->display_options['filters']['cdkey']['id'] = 'cdkey';
  $handler->display->display_options['filters']['cdkey']['table'] = 'cdkey';
  $handler->display->display_options['filters']['cdkey']['field'] = 'cdkey';
  $handler->display->display_options['filters']['cdkey']['operator'] = 'contains';
  $handler->display->display_options['filters']['cdkey']['exposed'] = TRUE;
  $handler->display->display_options['filters']['cdkey']['expose']['operator_id'] = 'cdkey_op';
  $handler->display->display_options['filters']['cdkey']['expose']['label'] = 'CDKey Key';
  $handler->display->display_options['filters']['cdkey']['expose']['operator'] = 'cdkey_op';
  $handler->display->display_options['filters']['cdkey']['expose']['identifier'] = 'cdkey';
  $handler->display->display_options['filters']['cdkey']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* 过滤规则: 代码: CDKey Type (bundle) */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'cdkey';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['operator'] = 'contains';
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'CDKey Type (bundle)';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['required'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['type']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['type']['group_info']['label'] = 'CDKey Type (bundle)';
  $handler->display->display_options['filters']['type']['group_info']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['group_info']['remember'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/cdkey/used';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'CDKey Used';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['title'] = 'CDKey Used';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';
  $translatables['cdkey_used'] = array(
    t('Defaults'),
    t('CDKey Used'),
    t('更多'),
    t('搜索'),
    t('重置'),
    t('排序依据'),
    t('升序'),
    t('降序'),
    t('标示'),
    t('标示用户'),
    t('CDKey'),
    t('CDKey Status'),
    t('.'),
    t(','),
    t('CDKey Type (bundle)'),
    t('标示时间'),
    t('名字'),
    t('CDKey Key'),
    t('Page'),
  );
  return $view;
}
