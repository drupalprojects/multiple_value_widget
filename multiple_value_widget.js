(function($) {

var widgets = {};

widgets.blocks = function($wrapper, settings) {

  var optionsSortable = {
    update: function(event, ui) {
      $wrapper.trigger('mvwOrderChanged');
    },
    delay: 100
  };

  $wrapper.sortable(optionsSortable);
};


widgets.accordion = function($wrapper, settings) {

  var optionsAccordion = {
    collapsible: true,
    active: false,
    header: '> div > .mvw-item-title'
  };

  var optionsSortable = {
    axis: 'y',
    handle: '.mvw-item-title',
    //stop: function( event, ui ) { ui.item.children('.mvw-item-title').triggerHandler('focusout'); },
    update: function(event, ui) {
      $wrapper.trigger('mvwOrderChanged');
    },
    delay: 100
  };

  $wrapper.accordion(optionsAccordion).sortable(optionsSortable);
};

widgets.tabs = function($wrapper, settings) {

};


var attachPlugin = function(context, id, widgetType, settings) {

  var weightClass = '.mvw-weight-delta-order';

  var $wrapper = $('#' + id);
  console.log($wrapper);

  //$(weightClass).hide();

  function updateWeights(event, ui) {
    var values = [];
    var $weights = $wrapper.find(weightClass);
    $weights.each(function() {
      values.push($(this).val());
    });
    values.sort();
    $weights.each(function() {
      $(this).val(values.shift());
    });
    console.log(event, ui);
  }

  $wrapper.bind('sortupdate', updateWeights);

  if(widgets[widgetType]) {
    widgets[widgetType]($wrapper, settings);
  }
};

/**
 * Main behavior for multiple value widget.
 */
Drupal.behaviors.multiple_value_widget = {
  attach: function (context, settings) {

    $.each(settings.mvw,function(id, type) {
      attachPlugin(context, id, type, settings);
    })

  }
};

})(jQuery);
