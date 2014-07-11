<?php

$plugin = array(
  'title' => 'Tabs',
  'process' => 'multiple_value_widget_plugin_tabs_process'
);

function multiple_value_widget_plugin_tabs_process(&$render) {

  $render['#attached']['library'][] = array('system', 'ui.tabs');

  $render['links'] = array(
    '#weight' => -1,
    '#theme'  => 'links',
    '#links'  => array(),
    '#attributes' => array('class' => array('mvw-tabs')),
  );
  foreach($render['#widgets'] as $delta => $widget) {
    $render['#links']['mvw-tab-' . $delta] = array(
      'href'     => '',
      'title'    => $widget['#title'],
      'html'     => TRUE,
      'fragment' => $widget['#group_id'],
      'external' => TRUE,
    );
  }
}