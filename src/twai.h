#pragma once
#include <Arduino.h>
#include "esp_twai.h"
#include "esp_twai_onchip.h"
#include "esp_twai_types.h"
#include <freertos/FreeRTOS.h>

esp_err_t twai_init();

void task_send(void *pvParameters);
void task_recv(void *pvParameters); 
void task_twai_status(void *pvParameters);
static bool twai_rx_cb(twai_node_handle_t handle, const twai_rx_done_event_data_t *edata, void *user_ctx);

extern xQueueHandle rx_queue;