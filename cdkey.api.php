<?php

function hook_cdkey_info() {
  return array(
    'sample' => array(
      'name' => 'sample',
      'description' => 'This is sample description'
    )
  );
}

function hook_cdkey_info_alter(&$types) {
  
}
