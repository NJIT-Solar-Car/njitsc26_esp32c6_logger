#include <Arduino.h>
#include <twai.h>

static const char *TAG = "TWAITest";


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  ESP_ERROR_CHECK(twai_init());
}

void loop()
{
  // put your main code here, to run repeatedly:
}
