<?php

class CDKeyType extends Entity {

  public $type;
  public $label;
  public $weight = 0;

  /**
   * Overridden constructor.
   */
  public function __construct($values = array()) {
    parent::__construct($values, 'cdkey_type');
  }

  /**
   * Determine if the entity is locked.
   */
  public function isLocked() {
    return isset($this->status) && empty($this->is_new) && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
  }

}

class CDKeyTypeController extends EntityAPIControllerExportable {

  /**
   * Rebuild menu after editing entity bundles.
   */
  public function save($entity, DatabaseTransaction $transaction = NULL) {
    parent::save($entity, $transaction);
    // Rebuild menu registry.
    variable_set('menu_rebuild_needed', TRUE);
  }

}

class CDKeyTypeUiController extends EntityDefaultUIController {

  /**
   * Override hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = 'Manage CDKey Types.';
    return $items;
  }

}

class CDKey extends Entity {

  /**
   * Define the label of the entity.
   */
  protected function defaultLabel() {
    return 'sn'; // $this->label;
  }

  /**
   * Specify the default uri, which is picked up by uri() by default.
   */
  protected function defaultUri() {
    return array('path' => 'admin/cdkey/' . entity_label($this->entityType, $this));
  }

}

class CDKeyController extends EntityAPIController {

  /**
   * Build a structured array representing the entity's content.
   */
  public function buildContent($entity, $view_mode = 'full', $langcdkey = NULL, $content = array()) {
    // Make "description" property themed like default fields.
    $content['description'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' => t('Description'),
      '#access' => TRUE,
      '#label_display' => 'above',
      '#view_mode' => 'full',
      '#language' => LANGUAGE_NONE,
      '#field_name' => 'field_fake_description',
      '#field_type' => 'text',
      '#entity_type' => 'cdkey',
      '#bundle' => $entity->type,
      '#items' => array(),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($entity->sn)),
    );

    return parent::buildContent($entity, $view_mode, $langcdkey, $content);
  }

}

class CDKeyUsed extends Entity {

  /**
   * Define the label of the entity.
   */
  protected function defaultLabel() {
    return 'sn'; // $this->label;
  }

  /**
   * Specify the default uri, which is picked up by uri() by default.
   */
  protected function defaultUri() {
    return array('path' => 'admin/cdkey/' . entity_label($this->entityType, $this));
  }

}

class CDKeyUsedController extends EntityAPIController {

  /**
   * Build a structured array representing the entity's content.
   */
  public function buildContent($entity, $view_mode = 'full', $langcdkey = NULL, $content = array()) {
    // Make "description" property themed like default fields.
    $content['description'] = array(
      '#theme' => 'field',
      '#weight' => 0,
      '#title' => t('Description'),
      '#access' => TRUE,
      '#label_display' => 'above',
      '#view_mode' => 'full',
      '#language' => LANGUAGE_NONE,
      '#field_name' => 'field_fake_description',
      '#field_type' => 'text',
      '#entity_type' => 'cdkey',
      '#bundle' => $entity->type,
      '#items' => array(),
      '#formatter' => 'text_default',
      0 => array('#markup' => check_plain($entity->sn)),
    );

    return parent::buildContent($entity, $view_mode, $langcdkey, $content);
  }

}
