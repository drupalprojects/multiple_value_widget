<?php

function template_preprocess_multiple_value_widget_widget_blocks(&$vars) {
  $element = &$vars['element'];

  $element['#attached']['library'][] = array('multiple_value_widget', 'widget_blocks');

  $element['#attributes']['class'][] = 'ui-widget';
  $element['#attributes']['class'][] = 'mvw-type-blocks';

  foreach(element_children($element['widgets']) as $key) {
    $widget = &$element['widgets'][$key];
    $widget['title']['#attributes']['class'][] = 'mvw-item-title';
    $widget['title']['#attributes']['class'][] = 'ui-corner-all';
    $widget['title']['#attributes']['class'][] = 'ui-widget-header';
    $widget['title']['value']['#markup'] .= '<span class="ui-icon ui-icon-minusthick"></span>';

    $widget['content']['#attributes']['class'][] = 'ui-widget-content';
  }
}

function theme_multiple_value_widget_widget_blocks($vars) {
  $element = $vars['element'];
  drupal_process_attached($element);
  return drupal_render_children($vars['element']);
}
