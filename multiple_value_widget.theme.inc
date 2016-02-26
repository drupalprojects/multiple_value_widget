<?php

/**
 * Implements template_preprocess_HOOK().
 */
function template_preprocess_multiple_value_widget_form(&$vars) {
  $element = &$vars['element'];

  foreach (element_children($element) as $delta) {
    if(is_int($delta)) {
      $element[$delta]['#title'] = $element['#title'] . ' (' . ($delta + 1) . ')';
      $element['#mvw']['widgets'][$delta] = &$element[$delta];
    }
  }
}

/**
 * Implements template_process_HOOK().
 */
function template_process_multiple_value_widget_form(&$vars) {
  $element = &$vars['element'];

  // Sort items according to '_weight' (needed when the form comes back after
  // preview or failed validation).
  usort($element['#mvw']['widgets'], '_field_sort_items_value_helper');
}


/**
 * Implements theme_HOOK().
 */
function theme_multiple_value_widget_form(&$vars) {

  $element     = $vars['element'];
  $widget_type = $element['#mvw']['widget_type'];
  $field_name  = $element['#mvw']['field_name'];
  $element_widgets = $element['#mvw']['widgets'];

  $id = "mvw-$field_name";

  $render = array();
  $render['widgets'] = array(
    '#prefix' => "<div id=\"$id\" class=\"mvw-type-$widget_type\">",
    '#suffix' => '</div>'
  );

  $render['#attached']['library'][] = array('multiple_value_widget', 'core');
  $render['#attributes']['data-draggable'] = '.mvw-item-title';
  $render['#attributes']['data-sortable'] = 1;

  $js_settings = array();
  $js_settings['mvw'][$id] = $widget_type;
  drupal_add_js($js_settings, 'setting');

  foreach ($element_widgets as $delta => $element_widget) {

    $render_widget = array(
      '#type' => 'container',
      '#title' => $element_widget['#title'],
      '#attributes' => array(
        'id' => 'mvw-group-' . $element['#field_name'] . '-' . $delta,
        'class' => array('mvw-item', 'delta-' . $delta),
      ),
    );

    $render_widget['title'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('mvw-item-title'),
      ),
      'value' => array(
        '#markup' => check_plain($element_widget['#title']),
      ),
    );

    $render_widget['content'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('mvw-item-content'),
      ),
      '#weight' => .001,
    ) + $element_widget;

    $render['widgets'][$delta] = $render_widget;
  }

  $render['add_more'] = $element['add_more'];
  $render['add_more']['#attributes']['class'][] = 'clearfix';

  $render['#widgets'] = $element_widgets;

  $widget = multiple_value_widget_get_widget($widget_type);
  $render['#theme'] = $widget['theme'];

  return drupal_render($render);
}


function theme_multiple_value_widget_file_widget_multiple($variables) {

  $element = $variables['element'];

  // Get our list of widgets in order (needed when the form comes back after
  // preview or failed validation).
  $widgets = array();
  foreach (element_children($element) as $key) {
    $widgets[] = &$element[$key];
  }

  $instance = field_read_instance($widgets[0]['#entity_type'], $widgets[0]['#field_name'], $widgets[0]['#bundle']);
  if (empty($instance['widget']['settings']['multiple_value_widget']) || $instance['widget']['settings']['multiple_value_widget'] == 'table') {
    return theme_file_widget_multiple($variables);
  }

  $widget_type = $instance['widget']['settings']['multiple_value_widget'];

  usort($widgets, '_field_sort_items_value_helper');

  $id = 'mvw-' . $element['#field_name'];

  multiple_value_widget_add_assets($id, $widget_type);

  $output = '<div id="' . $id . '" class="mvw-type-' . $widget_type . '">';

  $groups = array();
  foreach ($widgets as $delta => &$widget) {

    // Save the uploading row for last.
    if ($widget['#file'] == FALSE) {
      $widget['#title'] = $element['#file_upload_title'];
      $widget['#description'] = $element['#file_upload_description'];
      continue;
    }

    if (isset($widget['#file'])) {
      $title = '<span class="file">' . check_plain($widget['#file']->filename) . '</span>';
      $title .= ' <span class="file-size">(' . format_size($widget['#file']->filesize) . ')</span> ';
    }
    else {
      $title = $element['#title'] . ' (' . ($delta + 1) . ')';
    }
    $element['#delta'] = $delta;

    drupal_alter('multiple_value_widget_element_title', $title, $element);
    $group_id = 'mvw-group-' . $element['#field_name'] . '-' . $delta;

    if ($widget_type == 'tabs') {
      $links['mvw-tab-' . $delta] = array(
        'href' => '',
        'title' => $title,
        'html' => TRUE,
        'fragment' => $group_id,
        'external' => TRUE,
      );
    }

    // Render everything else together in a tabs, without the normal wrappers.
    $widget['#theme_wrappers'] = array();
    $widget['_weight']['#attributes']['class'] = array('mvw-weight-delta-order');

    $groups[$delta] = array(
      '#theme' => 'multiple_value_widget_group',
      '#title' => $title,
      '#widget_type' => $widget_type,
      '#attributes' => array(
        'id' => $group_id,
        'class' => array('mvw-group', 'delta-' . $delta),
      ),
      'widget' => $widget,
    );

    // Do not print widgets twice.
    hide($widget);

  }
  if ($widget_type == 'tabs' && isset($links)) {
    $attributes = array('class' => array('mvw-tabs'));
    $output .= theme('links', array('links' => $links, 'attributes' => $attributes));
  }
  $output .= render($groups);
  $output .= '</div>';

  $output .= drupal_render_children($element);

  return $output;

}
