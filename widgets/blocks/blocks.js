(function($, MVW) {

  var PluginBase = MVW.plugins.base;

  var PluginBlocks = function($wrapper) {
    PluginBase.call(this, $wrapper);
  };
  PluginBlocks.prototype = Object.create(PluginBase.prototype);
  PluginBlocks.prototype.constructor = PluginBlocks;
  PluginBlocks.prototype.attach = function() {
    var
      that = this,
      $toggleIcons = this.$wrapper.find('.mvw-item .mvw-item-title .ui-icon');

    PluginBase.prototype.attach.call(this);
    $toggleIcons.not('.ui-icon-processed').addClass('ui-icon-processed');
    $toggleIcons.click(function() {
      $(this)
        .toggleClass('ui-icon-minusthick ui-icon-plusthick')
        .parents('.mvw-item:first').find('.mvw-item-content').toggle();
    });
    this.$wrapper.sortable({
      delay: this.delay,
      update: function() {
        that.update();
      }
    });
  };

  MVW.plugins.blocks = PluginBlocks;

}(jQuery, MultipleValueWidget));
