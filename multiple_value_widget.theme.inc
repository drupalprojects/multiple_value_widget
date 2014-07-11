<?php

/**
 * Implements template_preprocess_HOOK().
 */
function template_preprocess_multiple_value_widget_form(&$vars) {
  $element = &$vars['elements'];

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
  $element = &$vars['elements'];

  // Sort items according to '_weight' (needed when the form comes back after
  // preview or failed validation).
  usort($element['#mvw']['widgets'], '_field_sort_items_value_helper');
  foreach($element['#mvw']['widgets'] as $delta => &$widget) {
    $widget['_weight']['#attributes']['class'] = array('mvw-weight-delta-order');
    $widget['#group_id'] = 'mvw-group-' . $element['#field_name'] . '-' . $delta;
  }
}


/**
 * Implements theme_HOOK().
 */
function theme_multiple_value_widget_form(&$vars) {

  $element     = $vars['elements'];
  $widget_type = $element['#mvw']['widget_type'];
  $widgets     = $element['#mvw']['widgets'];
  $field_name  = $element['#mvw']['field_name'];

  $id = "mvw-$field_name";

  $render = array();
  $render['widgets'] = array(
    '#prefix' => "<div id=\"$id\" class=\"mvw-type-$widget_type\">",
    '#suffix' => '</div>'
  );

  $path = drupal_get_path('module', 'multiple_value_widget');

  $render['#attached']['library'][] = array('system', 'ui.sortable');
  $render['#attached']['css'][]     = "$path/multiple_value_widget.css";
  $render['#attached']['js'][]      = "$path/multiple_value_widget.js";
  $render['#attached']['js'][]      = array('type' => 'setting', 'data' => array('mvw' => array($id => $widget_type)));
  $render['#attributes']['data-draggable'] = '.mvw-item-title';
  $render['#attributes']['data-sortable'] = 1;

  foreach ($widgets as $delta => $widget) {

    $render_widget = array();
    $render_widget['#type'] = 'container';
    $render_widget['#title'] = $widget['#title'];
    $render_widget['#attributes']['id'] = $widget['#group_id'];
    $render_widget['#attributes']['class'] = array('mvw-item', 'delta-' . $delta);

    $render_widget['title']['#type'] = 'container';
    $render_widget['title']['#attributes']['class'] = array('mvw-item-title');
    $render_widget['title']['value']['#markup'] = check_plain($widget['#title']);

    $render_widget['content']['#type'] = 'container';
    $render_widget['content']['#attributes']['class'] = array('mvw-item-content');
    $render_widget['content']['#weight'] = .001;
    $render_widget['content'] += $widget;

    $render['widgets'][$delta] = $render_widget;
  }

  $render['add_more'] = $element['add_more'];
  $render['add_more']['#attributes']['class'][] = 'clearfix';

  $render['#widgets'] = $widgets;

  ctools_include('plugins');
  $plugin = ctools_get_plugins('multiple_value_widget', 'widgets', $widget_type);
  // @todo ctools should have included the file automatically. Investigate.
  include_once $plugin['path'] . '/' . $plugin['file'];
  $plugin['process']($render);

  return drupal_render($render);
}



function theme_multiple_value_widget_ui_widget_title(&$vars) {

}

function theme_multiple_value_widget_ui_widget_content(&$vars) {

}



/**
 * Returns HTML for a single widget group.
 */
function theme_multiple_value_widget_group($vars) {
  $elements = $vars['elements'];

  if ($elements['#widget_type'] == 'blocks') {
    $ui_classes = array(
      'ui-helper-clearfix',
      'ui-corner-all',
    );
    $elements['#attributes']['class'] = array_merge($ui_classes, $elements['#attributes']['class']);
  }

  $render = array(
    '#prefix' => '<div' . drupal_attributes($elements['#attributes']) . '>',
    '#suffix' => '</div>'
  );

  switch ($elements['#widget_type']) {
    case 'accordion':
      $render['title'] = array(
        '#weight' => -1,
        '#prefix' => '<div class="mvw-item-title accordion">',
        '#suffix' => '</div>',
        '#markup' => '<a href="#">' . $elements['#title'] . '<span class="ui-icon ui-icon-arrowthick-2-n-s"></span></a>'
      );
      break;

    case 'blocks':
      $render['title'] = array(
        '#weight' => -1,
        '#prefix' => '<div class="mvw-item-title ui-widget-header ui-corner-all">',
        '#suffix' => '</div>',
        '#markup' => $elements['#title'] . '<span class="ui-icon ui-icon-minusthick"></span>'
      );
      break;

  }

  $render['content'] = $elements['content'];
  return drupal_render($render);
}
