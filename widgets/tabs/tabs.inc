<?php

function template_preprocess_multiple_value_widget_widget_tabs(&$vars) {
  $element = &$vars['element'];

  $element['#attached']['library'][] = array('multiple_value_widget', 'widget_tabs');

  $element['#attributes']['class'][] = 'ui-tabs';
  $element['#attributes']['class'][] = 'ui-widget-content';
  $element['#attributes']['class'][] = 'mvw-type-tabs';
  $element['#attributes']['class'][] = 'mvw-tabs';

  $links = array();

  foreach(element_children($element['widgets']) as $delta) {
    $widget = &$element['widgets'][$delta];

    $links['mvw-tab-' . $delta] = array(
      'href'     => '',
      'title'    => $widget['#title'],
      'html'     => TRUE,
      'fragment' => $widget['#attributes']['id'],
      'external' => TRUE,
    );
  }

  $element['widgets']['links'] = array(
    '#weight' => -1,
    '#theme'  => 'links',
    '#attributes' => array(
      'class' => array('ui-widget-header')
    ),
    '#links'  => $links,
  );
}

function theme_multiple_value_widget_widget_tabs($vars) {
  $element = $vars['element'];
  drupal_process_attached($element);
  return '<div' . drupal_attributes($element['#attributes']) . '>' . drupal_render_children($vars['element']) . '</div>';
}
