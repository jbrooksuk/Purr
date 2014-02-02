#include <pebble.h>

#define PURR_TIMEOUT 300000

static Window *window;
static TextLayer *text_layer;
static AppTimer *timer;

static void purr(void *data) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Purr...");
  vibes_long_pulse();

  timer = app_timer_register(PURR_TIMEOUT, purr, NULL);
}

int main(void) {
  window = window_create();
  window_stack_push(window, true);

  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
  text_layer = text_layer_create((GRect){ .origin = { 0, 50 }, .size = bounds.size });
  text_layer_set_text(text_layer, "Purr");
  text_layer_set_font(text_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(text_layer));

  timer = app_timer_register(PURR_TIMEOUT, purr, NULL);

  app_event_loop();
}