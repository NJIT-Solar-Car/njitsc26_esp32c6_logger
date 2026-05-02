#include <Arduino.h>
#include <twai.h>
#include <Adafruit_NeoPixel.h>

// The built-in NeoPixel on the ESP32-C6-DevKitC-1 is on GPIO 8
#define PIN        8 
#define NUMPIXELS  1 

// Set up the NeoPixel object
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // --- NeoPixel Setup ---
  pixels.begin(); // Initialize the NeoPixel strip object
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.setBrightness(50); // Set brightness to ~20% (0-255) so it doesn't blind you
  
  // ESP_ERROR_CHECK(twai_new_node_onchip(&node_config, &node_hdl));
  // ESP_ERROR_CHECK(twai_node_enable(node_hdl)); 
}

void loop() {
  
  pixels.setPixelColor(0, pixels.Color(255, 0, 0)); 
  pixels.show(); // Send the updated color to the hardware
  delay(500);

    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();   
  delay(500);
  
  
}