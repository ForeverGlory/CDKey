<div id="cdkey-use-<?php print $cdkey_type->type; ?>" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <div class="cdkey-type-name">
    <?php print $cdkey_type->name; ?>
  </div>
  <?php if ($cdkey_type->description): ?>
    <div class="cdkey-type-description">
      <?php print $cdkey_type->description; ?>
    </div>
  <?php endif; ?>
  <?php print render($cdkey_info); ?>
  <?php print render($cdkey_use_form); ?>
</div>
