#include <Arduino.h>
#include <twai.h>
#include <kbl/kbl.h>
#include <global_queues.h>

static const char *TAG = "TWAITest";


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  ESP_ERROR_CHECK(twai_init());
  ESP_ERROR_CHECK(kbl_init());
}

void loop()
{
  // put your main code here, to run repeatedly:

  //xQueueSend(tx_queue, &KBL_CCP_MONITOR2, portMAX_DELAY);
  vTaskDelay(pdMS_TO_TICKS(500));
}
