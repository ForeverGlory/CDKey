<?php

class CDKey extends Entity {

  protected function defaultUri() {
    return array('path' => 'admin/cdkey/' . entity_label($this->entityType, $this));
  }

}

class CDKeyController extends EntityAPIController {
  
}
