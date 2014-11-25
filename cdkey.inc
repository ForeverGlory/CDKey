<?php

define('CDKEY_IS_USEBLE', 0);
define('CDKEY_IS_USING', 1);
define('CDKEY_IS_USED', 2);
define('CDKEY_IS_DISABLE', 3);
define('CDKEY_IS_UNEXISTS', 4);
define('CDKEY_IS_NOTYET', 5);
define('CDKEY_IS_EXPIRED', 6);

/**
 * Using CDKey
 */
function cdkey_using($cdkey, $uid = NULL) {
  if ($uid === NULL) {
    $user = $GLOBALS['user'];
  } else {
    $user = user_load($uid);
  }
  if (!$user) {
    return FALSE;
  }
  if ($cdkey && cdkey_is_useble($cdkey, $uid)) {
    module_invoke_all('cdkey_using', $cdkey, $user);
    $flag = flag_get_flag('cdkey_used');
    $isFlag = $flag->flag('flag', entity_id('cdkey', $cdkey), $user);
    module_invoke_all('cdkey_used', $cdkey, $user);
    return $isFlag;
  }
  return FALSE;
}

function cdkey_validate($cdkey, $keyt) {
  module_invoke_all('cdkey_validate', $cdkey, $keyt);
  return $cdkey->keyt == $keyt;
}

function cdkey_status($cdkey) {
  if (!is_object($cdkey)) {
    $cdkey = cdkey_load($cdkey);
  }
  if (empty($cdkey)) {
    return CDKEY_IS_UNEXISTS;
  }
  $status = $cdkey->status;
  if ($status !== CDKEY_IS_DISABLE && flag_get_flag('cdkey_used')->get_count(entity_id('cdkey', $cdkey)) >= $cdkey->num) {
    $status = CDKEY_IS_USED;
  }
  drupal_alter('cdkey_status', $cdkey, $status);
  return $status;
}

/**
 * CDKey 是否可用
 * 如传递 Uid，则表示该用户是否可用该 CDKey
 * @return boolean
 */
function cdkey_is_useble($cdkey, $uid = NULL) {
  if (cdkey_status($cdkey) !== CDKEY_IS_USEBLE) {
    return FALSE;
  } elseif (empty($uid)) {
    return TRUE;
  }
  $flag = flag_get_flag('cdkey_used');
  if ($flag->get_count(entity_id('cdkey', $cdkey)) >= $cdkey->num) {
    return FALSE;
  }
  if ($flag->is_flagged(entity_id('cdkey', $cdkey), $uid)) {
    return FALSE;
  }
  return TRUE;
}

/**
 * CDKey 是否已被使用
 * @return boolean
 */
function cdkey_is_used($cdkey, $uid = NULL) {
  $status = cdkey_status($cdkey);
  if (empty($uid)) {
    if ($status === CDKEY_IS_USED) {
      return TRUE;
    } else {
      return FALSE;
    }
  } elseif ($status === CDKEY_IS_DISABLE || $status === CDKEY_IS_UNEXISTS) {
    return FALSE;
  } else {
    $flag = flag_get_flag('cdkey_used');
    return $flag->is_flagged(entity_id('cdkey', $cdkey), $uid);
  }
}
