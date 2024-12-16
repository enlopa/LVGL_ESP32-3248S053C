#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <Wire.h>
#include "TAMC_GT911.h"


#define TFT_ROTATION  LV_DISPLAY_ROTATION_0
// Create an instance of the TFT_eSPI library to interface wiht the SPI display - ST7796
TFT_eSPI tft = TFT_eSPI();

// TAMC_GT911 initialize
TAMC_GT911 tc = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, TFT_WIDTH, TFT_HEIGHT);

// LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes
#define DRAW_BUF_SIZE (TFT_WIDTH * TFT_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// LVGL Button
lv_obj_t * button;


//use Arduinos millis() as tick source
static uint32_t my_tick(void)
{
  return millis();
}

//Event handler for button
void button_event_cb(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);

  if (code == LV_EVENT_CLICKED) {
    
    lv_obj_t * label = lv_obj_get_child(button, 0); // The label is the only child of the button
    const char * txt = lv_label_get_text(label);
    
    if (strcmp(txt, "Button") == 0) {
      lv_label_set_text(label, "Clicked");  
    } else {
      lv_label_set_text(label, "Button");
    }
  }
}

// Fuction to read data from the touchpad using I2C
void touchread(lv_indev_t * indev_driver, lv_indev_data_t *data) {
  tc.read();

  if (tc.isTouched) {
    data->point.x = tc.points[0].y;
    data->point.y = tft.width()-tc.points[0].x;
    data->state = LV_INDEV_STATE_PRESSED;  // Button Pressed
  } else {
    data->state = LV_INDEV_STATE_RELEASED;  // Button Released
  }
}

void setup() {

  //Lvgl initialization
  lv_init();
 
  //Touch initialization
  tc.begin();
  tc.setRotation(0);
    
  // Set a tick source so that LVGL will know how much time elapsed.
  lv_tick_set_cb(my_tick);

   
  lv_display_t *disp = lv_tft_espi_create(TFT_WIDTH, TFT_HEIGHT, draw_buf, sizeof(draw_buf));
  lv_display_set_rotation(disp, TFT_ROTATION);

  lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);

  button = lv_button_create(lv_screen_active());                   //Add a button to the current screen
  lv_obj_center(button);                                           // Set its position
  lv_obj_set_size(button, 100, 50);                                // Set its size
  lv_obj_add_event_cb(button, button_event_cb, LV_EVENT_CLICKED, NULL); //Assign a callback to the button

  lv_obj_t * label = lv_label_create(button);                      // Add a label to the button
  lv_label_set_text(label, "Button");                              // Set the labels text
  lv_obj_center(label);                                            // Align the label to the center

  // Create input device as a pointer and a call back function for the touchpad
  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, touchread);
}

void loop() {
  lv_task_handler(); // let the GUI do its work
  delay(5); // let this time pass
}