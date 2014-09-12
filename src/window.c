#include "window.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_panda;
static GBitmap *s_res_image_cloud;
static GFont s_res_gothic_28_bold;
static BitmapLayer *s_bitmap_panda;
static BitmapLayer *s_bitmap_cloud;
static TextLayer *s_text_time;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, true);
  
  s_res_image_panda = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PANDA);
  s_res_image_cloud = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CLOUD);
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  // s_bitmap_panda
  s_bitmap_panda = bitmap_layer_create(GRect(34, 88, 100, 64));
  bitmap_layer_set_bitmap(s_bitmap_panda, s_res_image_panda);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmap_panda);
  
  // s_bitmap_cloud
  s_bitmap_cloud = bitmap_layer_create(GRect(10, 17, 100, 70));
  bitmap_layer_set_bitmap(s_bitmap_cloud, s_res_image_cloud);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmap_cloud);
  
  // s_text_time
  s_text_time = text_layer_create(GRect(19, 34, 80, 30));
  text_layer_set_background_color(s_text_time, GColorClear);
  text_layer_set_text_color(s_text_time, GColorWhite);
  text_layer_set_text(s_text_time, "00:00");
  text_layer_set_text_alignment(s_text_time, GTextAlignmentCenter);
  text_layer_set_font(s_text_time, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_text_time);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmap_panda);
  bitmap_layer_destroy(s_bitmap_cloud);
  text_layer_destroy(s_text_time);
  gbitmap_destroy(s_res_image_panda);
  gbitmap_destroy(s_res_image_cloud);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

static char time_buffer[16];
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  clock_copy_time_string(time_buffer, sizeof(time_buffer)/sizeof(*time_buffer));
  text_layer_set_text(s_text_time, time_buffer); 
}

void show_window(void) {
  initialise_ui();
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);

  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_window(void) {
  window_stack_remove(s_window, true);
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}
