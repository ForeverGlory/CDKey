<?php

/**
 * Implements hook_views_default_views().
 */
function cdkey_views_default_views() {
  $views = array();
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
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'cdkey administer';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No CDKey';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Field: CDKey: Cdkey ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'cdkey';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  /* Field: CDKey: Label */
  $handler->display->display_options['fields']['sn']['id'] = 'sn';
  $handler->display->display_options['fields']['sn']['table'] = 'cdkey';
  $handler->display->display_options['fields']['sn']['field'] = 'sn';
  /* Field: CDKey: Pass */
  $handler->display->display_options['fields']['pass']['id'] = 'pass';
  $handler->display->display_options['fields']['pass']['table'] = 'cdkey';
  $handler->display->display_options['fields']['pass']['field'] = 'pass';
  /* Field: CDKey: Edit */
  $handler->display->display_options['fields']['edit']['id'] = 'edit';
  $handler->display->display_options['fields']['edit']['table'] = 'views_entity_cdkey';
  $handler->display->display_options['fields']['edit']['field'] = 'edit';
  /* Field: CDKey: Delete */
  $handler->display->display_options['fields']['delete']['id'] = 'delete';
  $handler->display->display_options['fields']['delete']['table'] = 'views_entity_cdkey';
  $handler->display->display_options['fields']['delete']['field'] = 'delete';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/cdkey';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'CDKey';
  $handler->display->display_options['menu']['weight'] = '-9';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['title'] = 'cdddd';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $views['cdkey'] = $view;
  return $views;
}
