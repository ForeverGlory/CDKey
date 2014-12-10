<?php

class cdkey_handler_field_cdkey_delete extends cdkey_handler_field_cdkey_link {

  /**
   * Renders the link.
   */
  function render_link($cdkey, $values) {
    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = 'admin/cdkey/' . $cdkey->id . '/delete';
    $this->options['alter']['query'] = drupal_get_destination();

    $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    return $text;
  }

}
