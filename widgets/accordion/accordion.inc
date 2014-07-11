<?php

$plugin = array(
  'title' => 'Accordion',
  'process' => 'multiple_value_widget_plugin_accordion_process',
);

function multiple_value_widget_plugin_accordion_process(&$render) {
  $path = drupal_get_path('module', 'multiple_value_widget');
  $render['#attached']['css'][] = "$path/widgets/accordion/accordion.css";
  $render['#attached']['library'][] = array('system', 'ui.accordion');

  foreach(element_children($render['widgets']) as $key) {
    $widget = &$render['widgets'][$key];
    $widget['title']['value']['#prefix'] = '<a href="#">';
    $widget['title']['value']['#suffix'] = '<span class="ui-icon ui-icon-arrowthick-2-n-s"></span></a>';
  }
}
