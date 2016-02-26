(function($, MVW) {

  var PluginBase = MVW.plugins.base;

  var PluginAccordion = function($wrapper) {
    PluginBase.call(this, $wrapper);
  };
  PluginAccordion.prototype = Object.create(PluginBase.prototype);
  PluginAccordion.prototype.constructor = PluginAccordion;
  PluginAccordion.prototype.attach = function() {
    var that = this;
    PluginBase.prototype.attach.call(this);
    this.$wrapper.accordion({
      collapsible: true,
      active: false,
      header: '> div > .mvw-item-title'
    });
    this.$wrapper.sortable({
      axis: 'y',
      handle: '.mvw-item-title',
      delay: this.delay,
      update: function() {
        that.update();
      },
      stop: function(event, ui) {
        ui.item.children('.mvw-item-title').triggerHandler('focusout');
      }
    });
  };

  MVW.plugins.accordion = PluginAccordion;

}(jQuery, MultipleValueWidget));
