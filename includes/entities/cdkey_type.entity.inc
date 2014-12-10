<?php

class CDKeyType extends Entity {

  protected function defaultUri() {
    return array('path' => 'admin/cdkey/manage/' . entity_id($this->entityType, $this));
  }

}

class CDKeyTypeController extends EntityAPIController {
  
}
