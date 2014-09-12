#include <pebble.h>
#include "window.h"

static void init(void) {
  show_window();
}

static void deinit(void) {
  hide_window();
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
