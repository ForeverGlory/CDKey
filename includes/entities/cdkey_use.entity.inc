<?php

class CDKeyUse extends Entity {

  protected function defaultUri() {
    return array('path' => 'admin/cdkey/use/' . entity_id($this->entityType, $this));
  }

}

class CDKeyUseController extends EntityAPIController {

  public function count($conditions = array()) {
    $query = db_select($this->entityInfo['base table'], 'base');
    if ($conditions) {
      foreach ($conditions as $field => $value) {
        $query->condition('base.' . $field, $value);
      }
    }
    $query->addExpression('COUNT(*)');
    $count = $query->execute()->fetchField();
    return intval($count);
  }

}
