#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

// --- E32 Module Pin Definitions ---
// Change these to match your actual ESP32-C6 wiring
#define M0_PIN      4
#define M1_PIN      5
#define AUX_PIN     15

// Dedicated Serial port for the LoRa module
#define LORA_RX_PIN 17 // Connects to the TXD pin of the E32
#define LORA_TX_PIN 16 // Connects to the RXD pin of the E32

// --- ESP32-C6 Onboard LED ---
#define LED_PIN     8 
#define NUMPIXELS   1 
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // 1. Initialize Serial Monitor for debugging
  Serial.begin(115200);
  
  // 2. Initialize Hardware Serial for the E32 Module (Default baud rate is 9600)
  Serial1.begin(9600, SERIAL_8N1, LORA_RX_PIN, LORA_TX_PIN);

  // 3. Initialize the onboard RGB LED
  pixels.begin();
  pixels.clear();
  pixels.setBrightness(50); 
  
  // 4. Configure E32 Control Pins
  pinMode(M0_PIN, OUTPUT);
  pinMode(M1_PIN, OUTPUT);
  
  // AUX must be an input. It tells us what the module is doing.
  pinMode(AUX_PIN, INPUT_PULLUP); 

  // 5. Set to Mode 0: Normal Mode (M0 = 0, M1 = 0)
  digitalWrite(M0_PIN, LOW);
  digitalWrite(M1_PIN, LOW);
  
  Serial.println("E32 Module set to Normal Mode (M0=0, M1=0).");
  
  // Wait for AUX to go HIGH. 
  // AUX goes LOW during reset/mode-switch and returns HIGH when ready.
  while(digitalRead(AUX_PIN) == LOW) {
    delay(1);
  }
  Serial.println("Module Ready!");
}

void loop() {
  // ==========================================
  // PHASE 1: TRANSMISSION TEST
  // ==========================================
  String message = "Hello via LoRa!";
  Serial.println("\n--- Phase 1: Transmitting ---");
  Serial.println("Sending message: " + message);
  Serial1.print(message);
  
  // Wait a tiny fraction of a second for the module to pull AUX low
  

  Serial.print("1Waiting for transmission buffer to clear (AUX HIGH)...");
  unsigned long startTime = millis();
  bool timeout = false;


  // Wait in this loop until AUX goes HIGH again.
  while (digitalRead(AUX_PIN) == LOW) {
    if (millis() - startTime > 1000) { // 1 second timeout
      Serial.println(millis()-startTime);
      timeout = true;
      break;
    }
  }

  if (!timeout && digitalRead(AUX_PIN) == HIGH) {
    Serial.println(" DONE! AUX is HIGH.");
    // Success: Turn the LED Green
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
  } else {
    Serial.println(" TIMEOUT or AUX is stuck LOW.");
    // Failure: Turn the LED Red
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  }
  pixels.show(); 
  
  // First 5-second delay
  delay(5000); 

  // ==========================================
  // PHASE 2: IDLE STATE TEST
  // ==========================================
  Serial.println("\n--- Phase 2: Idle Check ---");
  Serial.print("Checking if AUX is resting HIGH... ");

  if (digitalRead(AUX_PIN) == HIGH) {
    Serial.println("YES. Module is completely idle and ready.");
    // Idle Success: Turn the LED Blue
    pixels.setPixelColor(0, pixels.Color(0, 0, 255));
  } else {
    Serial.println("NO! AUX is LOW.");
    Serial.println("  -> The module might be receiving data, resetting, or stuck.");
    // Idle Failure: Turn the LED Yellow
    pixels.setPixelColor(0, pixels.Color(255, 255, 0));
  }
  pixels.show();

  // Second 5-second delay before restarting the loop
  delay(5000); 
}