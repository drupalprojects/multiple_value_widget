<?php

$plugin = array(
  'title' => 'Blocks',
  'process' => 'multiple_value_widget_plugin_blocks_process',
);

function multiple_value_widget_plugin_blocks_process(&$render) {
  $path = drupal_get_path('module', 'multiple_value_widget');
  $render['#attached']['css'][] = "$path/widgets/blocks/blocks.css";
  $render['#attached']['library'][] = array('system', 'ui.blocks');

  $render['#attributes']['class'][] = 'ui-widget';

  foreach(element_children($render['widgets']) as $key) {
    $widget = &$render['widgets'][$key];
    $widget['title']['#attributes']['class'][] = 'ui-widget-header';
    $widget['content']['#attributes']['class'][] = 'ui-widget-content';
  }
}
