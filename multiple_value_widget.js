(function($) {

var attachPlugin = function(context, id, widget_type) {

  var tabsClass = '.mvw-tabs';
  var rowClass = '.mvw-group';
  var weightClass = '.mvw-weight-delta-order';

  var wrapper = $('#' + id);

  $(weightClass).hide();

  var updateField =  function (event, ui) {

    var siblings = [];

    if (widget_type == 'tabs') {
      $(tabsClass + ' li a', wrapper).each(function() {
        var sibling = $($(this).attr('href')).get(0);
        siblings.push(sibling)
      })
      var targetElement = $(weightClass, $($('a', ui.item.context).attr('href'))).get(0);
    }
    else {
      $(rowClass, wrapper).each(function(){siblings.push(this)})
      var targetElement = $(weightClass, $(ui.item.context)).get(0);
    }

    if ($(targetElement).is('select')) {

      // Get a list of acceptable values.
      var values = [];
      $('option', targetElement).each(function () {
        values.push(this.value);
      });

      var maxVal = values[values.length - 1];

      // Populate the values in the siblings.
      $(weightClass, siblings).each(function () {
        // If there are more items than possible values, assign the maximum value to the row.
        if (values.length > 0) {
          this.value = values.shift();
        }
        else {
          this.value = maxVal;
        }
      });
    }
    else {
      // Assume a numeric input field.
      var weight = parseInt($(weightClass, siblings[0]).val(), 10) || 0;
      $(weightClass, siblings).each(function () {
        this.value = weight;
        weight++;
      });
    }

  }

  if (widget_type == 'tabs') {
    var tabs = wrapper.tabs();
    tabs.find( ".ui-tabs-nav" )
    .sortable({
      axis: "x",
      stop: function() { tabs.tabs( "refresh" ); },
      update: updateField
    });
  }
  else {
    wrapper
    .accordion({
      collapsible: true,
      active: false ,
      header: "> div > h3",
    })
    .sortable({
        axis: "y",
        handle: "h3",
        stop: function( event, ui ) { ui.item.children( "h3" ).triggerHandler( "focusout" ); },
        update: updateField,
        delay: 100
    });
  }

}

/**
 * Main behavior for multiple value widget.
 */
Drupal.behaviors.multiple_value_widget = {
  attach: function (context, settings) {

    $.each(settings.mvw,function(id, type) {
      attachPlugin(context, id, type);
    })

  }
};

})(jQuery);
