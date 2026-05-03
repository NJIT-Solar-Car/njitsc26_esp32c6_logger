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
  pinMode(INPUT_PIN, INPUT_PULLDOWN);

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
  
  
  Serial0.write("1111111111111111111111111111111111111111111111111111111111");
  
  delay(4);
  
  
  if (digitalRead(INPUT_PIN) == HIGH) {
     
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    
    Serial.println("I can speak"); 
  } else {
    
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    Serial.println("I can't speak");
  }
  
  Serial0.write("1111111111111111111111111111111111111111111111111111111111");
  
  delay(3);
  
  
  if (digitalRead(INPUT_PIN) == HIGH) {
     
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    
    Serial.println("I can speak"); 
  } else {
    
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    Serial.println("I can't speak");
  }
  
  Serial0.write("1111111111111111111111111111111111111111111111111111111111");
  
  delay(2);
  
  
  if (digitalRead(INPUT_PIN) == HIGH) {
     
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    
    Serial.println("I can speak"); 
  } else {
    
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    Serial.println("I can't speak");
  }

  Serial0.write("1111111111111111111111111111111111111111111111111111111111");
  
  delay(1);
  
  
  if (digitalRead(INPUT_PIN) == HIGH) {
     
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    
    Serial.println("I can speak"); 
  } else {
    
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    Serial.println("I can't speak");
  }

  
  delay(500);
  
  
  if (digitalRead(INPUT_PIN) == HIGH) {
     
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    
    Serial.println("I can speak even though you never told me to? "); 
  } else {
    
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    Serial.println("I can't speak even though you never told me to? ");
  }

  delay(10000);

if (digitalRead(INPUT_PIN) == HIGH) {
     
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
    
    Serial.println("I can speak for some odd reason final check "); 
  } else {
    
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    Serial.println("I can't speak even though you never told me to? ");
  }


  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();  
  
 
}