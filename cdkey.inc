<?php

/**
 * 不存在
 */
define('CDKEY_IS_NOEXISTS', 0);
/**
 * 可使用
 */
define('CDKEY_IS_USABLE', 1);
/**
 * 使用中
 */
define('CDKEY_IS_USING', 2);
/**
 * 已使用
 */
define('CDKEY_IS_USED', 3);
/**
 * 不可用
 */
define('CDKEY_IS_DISABLED', 4);

/**
 * CDKey status
 * @return 
 */
function cdkey_status($cdkey, $uid = NULL) {
  $account = $uid ? user_load($uid) : $GLOBALS['user'];
  $statuses = &drupal_static(__FUNCTION__, array());
  if (isset($statuses[$account->uid][$cdkey->id])) {
    return $statuses[$account->uid][$cdkey->id];
  }
  $status = $cdkey->status; //CDKEY_IS_USABLE;
  $cdkey_type = cdkey_type_load($cdkey->type);
  $rules = $cdkey_type->data['rules'];

  if ($status == CDKEY_IS_USABLE && !empty($rules['limit'])) {
    //使用总数限制，没有限制则还可使用
    if (!empty($rules['limit']['sum'])) {
      //总数限制 小于 使用个数，大于则还可使用
      if ($rules['limit']['sum'] <= cdkey_use_count($cdkey)) {
        //总数 小于 使用人数，不可用
        $status = CDKEY_IS_DISABLED;
        if (cdkey_use_count($cdkey, $account->uid, CDKEY_IS_USING)) {
          //本人有使用中的
          $status = CDKEY_IS_USING;
        } elseif (cdkey_use_count($cdkey, $account->uid, CDKEY_IS_USED)) {
          //本人有已使用的
          $status = CDKEY_IS_USED;
        }
      }
    }
    if ($status === CDKEY_IS_USABLE && !empty($rules['limit']['user'])) {
      //同一用户能使用几次
      if ($rules['limit']['user'] <= cdkey_use_count($cdkey, $account->uid)) {
        $status = CDKEY_IS_USED;
        if (cdkey_use_count($cdkey, $account->uid, CDKEY_IS_USING)) {
          $status = CDKEY_IS_USING;
        }
      }
    }
  }
  drupal_alter('cdkey_status', $cdkey, $status, $account);
  $statuses[$account->uid][$cdkey->id] = $status;
  return $status;
}

/**
 * CDKey 是否可用，使用中，也是可用
 * 如传递 Uid，则表示该用户是否可用该 CDKey
 * @return boolean
 */
function cdkey_is_useble($cdkey, $uid = NULL) {
  return in_array(cdkey_status($cdkey, $uid), array(CDKEY_IS_USABLE, CDKEY_IS_USING));
}

/**
 * CDKey 是否已被使用
 * @return boolean
 */
function cdkey_is_used($cdkey, $uid = NULL) {
  return cdkey_status($cdkey, $uid) == CDKEY_IS_USED;
}

function cdkey_use_create($cdkey, $uid = NULL) {
  $account = $uid ? user_load($uid) : $GLOBALS['user'];
  if (cdkey_use_count($cdkey, $account->uid, CDKEY_IS_USING)) {
    $entities = entity_get_controller('cdkey_use')->load(FALSE, array(
      'type' => $cdkey->type,
      'sn' => $cdkey->sn,
      'status' => CDKEY_IS_USING,
      'uid' => $account->uid
    ));
    $cdkey_use = reset($entities);
  } else {
    $cdkey_use = entity_create('cdkey_use', array(
      'type' => $cdkey->type,
      'sn' => $cdkey->sn,
      'status' => CDKEY_IS_USABLE,
      'uid' => $account->uid
    ));
  }
  return $cdkey_use;
}

/**
 * CDKey使用统计
 * @return
 */
function cdkey_use_count($cdkey, $uid = NULL, $status = NULL) {
  $conditions = array(
    'sn' => $cdkey->sn,
    'type' => $cdkey->type,
  );
  if (isset($uid)) {
    $conditions['uid'] = intval($uid);
  }
  if (isset($status)) {
    $conditions['status'] = $status;
  }
  return entity_get_controller('cdkey_use')->count($conditions);
}
