#include <pebble.h>

#define PURR_INTERVAL 5

static Window *window;
static TextLayer *text_layer;

static void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {
  int minute = tick_time->tm_min;

  if (minute % PURR_INTERVAL == 0) {
    vibes_double_pulse();
  }
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Subscribe to the tick timer event service;
  tick_timer_service_subscribe(MINUTE_UNIT, handle_minute_tick);
}

static void init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
  });
  window_set_fullscreen(window, true);
  const bool animated = false;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  app_event_loop();
  deinit();
}
