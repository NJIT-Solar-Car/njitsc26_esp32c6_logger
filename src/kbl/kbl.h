#pragma once
#include <Arduino.h>
#include "esp_twai_types.h"

extern const twai_frame_t KBL_CCP_MONITOR2;
uint16_t kbl_getRPM(uint8_t data[8]);
uint16_t kbl_getCurrent(uint8_t data[8]);
