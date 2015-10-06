<?php

function template_preprocess_multiple_value_widget_widget_accordion(&$vars) {
  $render = &$vars['element'];
  $render['#attached']['library'][] = array('multiple_value_widget', 'widget_accordion');

  $element['#attributes']['class'][] = 'ui-widget';
  $element['#attributes']['class'][] = 'mvw-type-accordion';

  foreach(element_children($render['widgets']) as $key) {
    $widget = &$render['widgets'][$key];
    $widget['title']['value']['#prefix'] = '<a href="#">';
    $widget['title']['value']['#suffix'] = '<span class="ui-icon ui-icon-arrowthick-2-n-s"></span></a>';
  }
}

function theme_multiple_value_widget_widget_accordion($vars) {
  $element = $vars['element'];
  drupal_process_attached($element);
  return drupal_render_children($vars['element']);
}
