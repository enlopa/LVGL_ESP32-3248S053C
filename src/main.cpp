#include <Arduino.h>
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <Wire.h>
#include "TAMC_GT911.h"


#define TFT_ROTATION  LV_DISPLAY_ROTATION_0
TFT_eSPI tft = TFT_eSPI();

// TAMC_GT911 initialize
TAMC_GT911 tc = TAMC_GT911(TOUCH_SDA, TOUCH_SCL, TOUCH_INT, TOUCH_RST, TFT_WIDTH, TFT_HEIGHT);

/*LVGL draw into this buffer, 1/10 screen size usually works well. The size is in bytes*/
#define DRAW_BUF_SIZE (TFT_WIDTH * TFT_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

// LVGL Label to write on the screen
lv_obj_t * button;


/*use Arduinos millis() as tick source*/
static uint32_t my_tick(void)
{
  return millis();
}

void button_event_cb(lv_event_t * e)
{
  lv_event_code_t code = lv_event_get_code(e);

  if (code == LV_EVENT_CLICKED) {
    
    lv_obj_t * label = lv_obj_get_child(button, NULL); /*The label is the only child*/
    const char * txt = lv_label_get_text(label);
    
    if (strcmp(txt, "Button") == 0) {
      lv_label_set_text(label, "Clicked");  
    } else {
      lv_label_set_text(label, "Button");
    }
    //return LV_RES_OK;   /*The button is not deleted*/
  }
}

/*
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map)
{
  uint32_t w = lv_area_get_width(area);
  uint32_t h = lv_area_get_height(area);

  // Updates UI, without it we see dark screen
  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.writePixels((lgfx::rgb565_t *)px_map, w * h);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}
*/

// Función para leer los datos del tactil mediante I2C
void touchread(lv_indev_t * indev_driver, lv_indev_data_t *data) {
  tc.read();

  //Serial.println("Veamos....");

  if (tc.isTouched) {
    
    // Las coordenadas X e Y de la pantalla táctil se almacenan en buffer
    //uint16_t x = ((uint16_t)(buffer[3] & 0x0F) << 8) | buffer[4];  // Coordenada X
    //uint16_t y = ((uint16_t)(buffer[5] & 0x0F) << 8) | buffer[6];  // Coordenada Y
    
    data->point.x = tc.points[0].y;
    data->point.y = tft.width()-tc.points[0].x;
    
    //char toshow[50];
    //int i=0;
    //sprintf(toshow, "Pos : x= %d / y= %d ", tc.points[i].x, tc.points[i].y);
     
    data->state = LV_INDEV_STATE_PRESSED;  // Estado presionado
  } else {
    data->state = LV_INDEV_STATE_RELEASED;  // Estado liberado
  }
}


void setup() {

  Serial.begin(115200);
  // Stop I2C
  //Wire.end();
  Serial.println("Empezamos....");


  lv_init();
 
  tc.begin();
  tc.setRotation(0);
  //tc.setRotation(ROTATION_NORMAL);
  
  /*Set a tick source so that LVGL will know how much time elapsed. */
  lv_tick_set_cb(my_tick);

   // Inicializar la pantalla TFT con TFT_eSPI
  //tft.begin();
  //tft.setRotation(1);  // Ajustar la rotación de la pantalla

  lv_display_t *disp = lv_tft_espi_create(TFT_WIDTH, TFT_HEIGHT, draw_buf, sizeof(draw_buf));
  lv_display_set_rotation(disp, TFT_ROTATION);



  lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);


  //lv_obj_t * button = lv_button_create(lv_screen_active());                   /*Add a button to the current screen*/
  button = lv_button_create(lv_screen_active());                   /*Add a button to the current screen*/
  lv_obj_center(button);                                             /*Set its position*/
  lv_obj_set_size(button, 100, 50);                                  /*Set its size*/
  lv_obj_add_event_cb(button, button_event_cb, LV_EVENT_CLICKED, NULL); /*Assign a callback to the button*/

  lv_obj_t * label = lv_label_create(button);                        /*Add a label to the button*/
  lv_label_set_text(label, "Button");                             /*Set the labels text*/
  lv_obj_center(label);                                           /*Align the label to the center*/

  
  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, touchread);
}

void loop() {
  lv_task_handler(); /* let the GUI do its work */
  delay(5); /* let this time pass */
}