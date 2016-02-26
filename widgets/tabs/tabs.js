(function($, MVW) {

  var PluginBase = MVW.plugins.base;

  var PluginTabs = function($wrapper) {
    PluginBase.call(this, $wrapper);
  };
  PluginTabs.prototype = Object.create(PluginBase.prototype);
  PluginTabs.prototype.constructor = PluginTabs;
  PluginTabs.prototype.attach = function() {
    PluginBase.prototype.attach.call(this);
    var
      that = this,
      $tabs = this.$wrapper.tabs(),
      $tabNav = $tabs.find('.ui-tabs-nav');

    $tabNav.sortable({
      axis: 'x',
      delay: this.delay,
      update: function() {
        that.update();
      },
      stop: function() {
        $tabs.tabs('refresh');
      }
    });
    // The order of panels is static. To provide a simple way of determining
    // the tab position we link each tab to its weight field via .data().
    $tabNav.children().each(function() {
      var
        selector = $(this).find('a').attr('href'),
        $panel = that.$wrapper.find(selector),
        $weight = $panel.find(that.$weights);
      $weight.data('mvw-tab', this);
    });
  };
  PluginTabs.prototype.sortElementsByIndex = function(a, b) {
    // Retrieve the corresponding tab for each element.
    a = $(a).data('mvw-tab');
    b = $(b).data('mvw-tab');
    return PluginBase.prototype.sortElementsByIndex.call(this, a, b);
  };

  MVW.plugins.tabs = PluginTabs;

}(jQuery, MultipleValueWidget));
