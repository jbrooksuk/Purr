#include <pebble.h>

#define PURR_INTERVAL 1

static Window *window;
static TextLayer *text_layer;
static AppTimer *timer;

static void purr(void *data) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Purr...");
  vibes_long_pulse();
}

int main(void) {
  window = window_create();
  window_stack_push(window, true);

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  // text_layer = text_layer_create(bounds);

  timer = app_timer_register(300000, purr, NULL);

  app_event_loop();
}