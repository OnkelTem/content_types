<?php
// $Id$

/**
 * @file
 * Admin settings for OG Content types module.
 */

/**
 * Provide an overview of the administrator settings form.
 */
function og_content_types_admin_form($form, &$form_state) {
  $form = array();

  $content_types = node_type_get_types();
  foreach ($content_types as $key => $type) {

    if (og_is_group_type('node', $key)) {

      $options = array();
      $fields = field_info_instances('node', $key);
      foreach ($fields as $name => $field) {
        if ($field['widget']['module'] == 'field_content_types') {
          $options[$name] = $field['label'];
        }
      }
      $form['og_content_types_'. $key] = array(
        '#title' => $type->name,
        '#type' => 'select',
        '#options' => $options
          ? array(t('- Select Content Type field -')) + $options
          : array(t('- No Content Type field -')),
        '#disabled' => $options ? FALSE : TRUE,
        '#default_value' => variable_get('og_content_types_'. $key),
      );
    }

  }

  return system_settings_form($form);
}