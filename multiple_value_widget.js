(function($) {

  var attachPlugin = function(context, id, widget_type) {



    var weightClass = '.mvw-weight-delta-order';

    var wrapper = $('#' + id);
    if (widget_type == 'blocks') {
      $('.mvw-item .mvw-item-title .ui-icon', wrapper )
        .not('.ui-icon-processed')
        .addClass("ui-icon-processed")
        .click(function() {
          $(this)
            .toggleClass("ui-icon-minusthick")
            .toggleClass( "ui-icon-plusthick" )
            .parents('.mvw-item:first').find('.mvw-item-content').toggle();
        });
    }

    $(weightClass).hide();

    function updateField(event, ui) {

      var siblings = [], $targetElement;

      switch(widget_type) {

        case 'tabs':
          $('.mvw-tabs li a', wrapper).each(function() {
            var sibling = $($(this).attr('href')).get(0);
            siblings.push(sibling)
          });
          $targetElement = $(weightClass, $($('a', ui.item.context).attr('href')));
          break;

        default:
          $('.mvw-item', wrapper).each(function(){
            siblings.push(this)
          });
          $targetElement = $(weightClass, $(ui.item.context));
          break;
      }

      if ($targetElement.is('select')) {

        // Get a list of acceptable values.
        var values = [];
        $('option', $targetElement).each(function () {
          values.push(this.value);
        });

        var maxVal = values[values.length - 1];

        // Populate the values in the siblings.
        $(weightClass, siblings).each(function () {
          // If there are more items than possible values, assign the maximum value to the row.
          this.value = values.length > 0 ? values.shift() : maxVal;
        });
      }
      else {
        // Assume a numeric input field.
        var weight = parseInt($(weightClass, siblings[0]).val(), 10) || 0;
        $(weightClass, siblings).each(function () {
          this.value = weight++;
        });
      }

    }

    switch (widget_type) {
      case 'tabs':
        var tabs = wrapper.tabs();
        tabs.find( ".ui-tabs-nav" )
          .sortable({
            axis: "x",
            stop: function() { tabs.tabs( "refresh" ); },
            update: updateField,
            delay: 100
          });
        break;

      case 'accordion':
        wrapper
          .accordion({
            collapsible: true,
            active: false ,
            header: '> div > .mvw-item-title'
          })
          .sortable({
            axis: 'y',
            handle: '.mvw-item-title',
            stop: function( event, ui ) { ui.item.children('.mvw-item-title').triggerHandler('focusout'); },
            update: updateField,
            delay: 100
          });
        break;

      case 'blocks':
        wrapper
          .sortable({
            update: updateField,
            delay: 100
          });

        break;

    }

  }

  /**
   * Main behavior for multiple value widget.
   */
  Drupal.behaviors.multiple_value_widget = {
    attach: function (context, settings) {

      if (settings.mvw) {
        $.each(settings.mvw, function (id, type) {
          attachPlugin(context, id, type);
        });
      }

    }
  };

})(jQuery);
