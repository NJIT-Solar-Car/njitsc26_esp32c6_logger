#pragma once
#include <Arduino.h>
#include "esp_twai_types.h"
#include <freertos/FreeRTOS.h>
#include <global_queues.h>

extern const twai_frame_t KBL_CCP_A2D_BATCH_READ2;
extern const twai_frame_t KBL_CCP_MONITOR1;
extern const twai_frame_t KBL_CCP_MONITOR2;

esp_err_t kbl_init();

uint16_t kbl_getRPM(uint8_t data[8]);
uint16_t kbl_getCurrent(uint8_t data[8]);
void task_kbl_queries(void *pvParameters);