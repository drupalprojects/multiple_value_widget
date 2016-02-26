(function($) {

  var PluginBase = function($wrapper) {
    this.$wrapper = $wrapper;
    this.$weights = $wrapper.find(this.selectorWeight);
  };
  PluginBase.prototype.selectorWeight = '.mvw-weight-delta-order';
  PluginBase.prototype.delay = 100;
  PluginBase.prototype.attach = function() {
    this.$weights.hide();
  };
  PluginBase.prototype.sortElementsByIndex = function(a, b) {
    if(a.compareDocumentPosition) {
      return (a.compareDocumentPosition(b) & document.DOCUMENT_POSITION_PRECEDING) ? 1 : -1;
    }
    return a.sourceIndex - b.sourceIndex;
  };
  PluginBase.prototype.update = function() {
    this.$weights.sort(this.sortElementsByIndex);
    this.$weights.each(function(index) {
      this.value = index;
    });
  };

  window.MultipleValueWidget = window.MultipleValueWidget || {
    plugins: {
      base: PluginBase
    }
  };

  /**
   * Main behavior for multiple value widget.
   */
  Drupal.behaviors.multiple_value_widget = {
    attach: function(context, settings) {
      if(settings.mvw) {
        $.each(settings.mvw, function(id, type) {
          var $wrapper = $('#' + id, context);
          if(typeof MultipleValueWidget.plugins[type] === 'function' && $wrapper.length) {
            var plugin = new MultipleValueWidget.plugins[type]($wrapper);
            plugin.attach();
          }
        });
      }
    }
  };

})(jQuery);
