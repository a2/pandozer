#include "window.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GBitmap *s_res_image_cloud;
static GFont s_res_gothic_28_bold;
static GBitmap *s_res_image_panda;
static GBitmap *s_res_image_panda_eye;
static BitmapLayer *s_bitmap_cloud;
static TextLayer *s_text_time;
static BitmapLayer *s_bitmap_panda;
static BitmapLayer *s_bitmap_panda_eye;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, 1);
  
  s_res_image_cloud = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CLOUD);
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_image_panda = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PANDA);
  s_res_image_panda_eye = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PANDA_EYE);
  // s_bitmap_cloud
  s_bitmap_cloud = bitmap_layer_create(GRect(5, 7, 134, 82));
  bitmap_layer_set_bitmap(s_bitmap_cloud, s_res_image_cloud);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmap_cloud);
  
  // s_text_time
  s_text_time = text_layer_create(GRect(20, 37, 104, 30));
  text_layer_set_background_color(s_text_time, GColorClear);
  text_layer_set_text_color(s_text_time, GColorWhite);
  text_layer_set_text(s_text_time, " ");
  text_layer_set_text_alignment(s_text_time, GTextAlignmentCenter);
  text_layer_set_font(s_text_time, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_text_time);
  
  // s_bitmap_panda
  s_bitmap_panda = bitmap_layer_create(GRect(32, 92, 102, 66));
  bitmap_layer_set_bitmap(s_bitmap_panda, s_res_image_panda);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmap_panda);
  
  // s_bitmap_panda_eye
  s_bitmap_panda_eye = bitmap_layer_create(GRect(43, 125, 17, 19));
  bitmap_layer_set_bitmap(s_bitmap_panda_eye, s_res_image_panda_eye);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmap_panda_eye);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmap_cloud);
  text_layer_destroy(s_text_time);
  bitmap_layer_destroy(s_bitmap_panda);
  bitmap_layer_destroy(s_bitmap_panda_eye);
  gbitmap_destroy(s_res_image_cloud);
  gbitmap_destroy(s_res_image_panda);
  gbitmap_destroy(s_res_image_panda_eye);
}
// END AUTO-GENERATED UI CODE

static void app_timer_callback_open_panda_eye(void *data);
static void app_timer_callback_close_panda_eye(void *data);

static void handle_window_unload(Window* window) {
  destroy_ui();
}

static char time_buffer[16];
static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  clock_copy_time_string(time_buffer, sizeof(time_buffer)/sizeof(*time_buffer));
  text_layer_set_text(s_text_time, time_buffer);
  
  layer_set_hidden((Layer *)s_bitmap_panda_eye, true);

  uint32_t timeout = 1000;
  bool hidden = false;
  for (int i = 0; i < 5; i++) {
    AppTimerCallback callback = (hidden ? app_timer_callback_open_panda_eye : app_timer_callback_close_panda_eye);
    app_timer_register(timeout, callback, NULL);
    
    hidden = !hidden;
    timeout += 500;
  }
}

static void app_timer_callback_open_panda_eye(void *data) {
  layer_set_hidden((Layer *)s_bitmap_panda_eye, true);
}

static void app_timer_callback_close_panda_eye(void *data) {
  layer_set_hidden((Layer *)s_bitmap_panda_eye, false);
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
  tick_timer_service_unsubscribe();
}
