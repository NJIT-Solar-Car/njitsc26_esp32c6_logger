#include <Arduino.h>
#include <twai.h>

void setup() {
  // put your setup code here, to run once:
  ESP_ERROR_CHECK(twai_new_node_onchip(&node_config, &node_hdl));
  ESP_ERROR_CHECK(twai_node_enable(node_hdl)); 
}

void loop() {
  // put your main code here, to run repeatedly:
}
