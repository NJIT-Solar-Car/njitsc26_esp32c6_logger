#include <Arduino.h>
#include <twai.h>
#include <Adafruit_NeoPixel.h>

#define PIN        8 
#define NUMPIXELS  1 
#define INPUT_PIN  15 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  
  pixels.begin();
  pixels.clear();
  pixels.setBrightness(50); 
  pinMode(INPUT_PIN, INPUT);

  if (digitalRead(INPUT_PIN) == HIGH) {
     // Set to Red
    pixels.setPixelColor(0, pixels.Color(255, 0, 0)); 
  } else {
    
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  }

  // ESP_ERROR_CHECK(twai_new_node_onchip(&node_config, &node_hdl));
  // ESP_ERROR_CHECK(twai_node_enable(node_hdl)); 
  Serial.begin(9600);
}

void loop() {
  
  if (digitalRead(INPUT_PIN) == HIGH) {
     
    pixels.setPixelColor(0, pixels.Color(255, 0, 0)); 
  } else {
    
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  }
  
  Serial0.write("Hello");
  

 if (digitalRead(INPUT_PIN) == HIGH) {
    pixels.setPixelColor(0, pixels.Color(255, 0, 0)); 
  } else {
    
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  }
   
  if(Serial.available()) {
    char input = Serial.read(); 
Serial.println("I read" + input);
} else {
Serial.println("No data available"); 
}
  
  pixels.show();  
  
    delay(500); 
}