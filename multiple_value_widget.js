(function($) {

/**
 *
 */
Drupal.behaviors.multiple_value_widget_accordion = {
  attach: function (context, settings) {

    var wrapperClass = '.multiple_value_widget_accordion';
    var rowClass = '.mvw-group';
    var weightClass = '.mvw-weight-delta-order';

    $(weightClass).hide();

    var updateField =  function (event, ui) {

      var wrapper = $(ui.item.context).parents(wrapperClass)
      
      var siblings = [];
      $(rowClass, wrapper).each(function(){siblings.push(this)})
    
      var targetElement = $(weightClass, $(ui.item.context)).get(0);

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

    jQuery(wrapperClass)
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
};

})(jQuery);
