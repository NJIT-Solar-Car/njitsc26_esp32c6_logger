#include <kbl/kbl.h>

// these being 8 is intentional because of the printf statement that 
// prints out the whole frame
uint8_t CCP_MONITOR1[8] = {0x33};
uint8_t CCP_MONITOR2[8] = {0x37};
uint8_t CCP_A2D_BATCH_READ2[8] = {0x1A}; 

const uint8_t KBL_SEND_ADDR = 0x6B;

const twai_frame_t KBL_CCP_A2D_BATCH_READ2 = {
    .header = {
        .id = KBL_SEND_ADDR,
        .ide = false
    },
    .buffer = CCP_A2D_BATCH_READ2,
    .buffer_len = 1
};

const uint16_t CCP_A2D_BATCH_READ2_SEND_ADDR = 0x80;

const twai_frame_t KBL_CCP_MONITOR1 = {
    .header = {
        .id = KBL_SEND_ADDR,
        .ide = false
    },
    .buffer = CCP_MONITOR1,
    .buffer_len = 1
};

const uint16_t CCP_MONITOR1_SEND_ADDR = 0x81;

const twai_frame_t KBL_CCP_MONITOR2 = {
    .header = {
        .id = KBL_SEND_ADDR,
        .ide = false
    },
    .buffer = CCP_MONITOR2,
    .buffer_len = 1
};

const uint16_t CCP_MONITOR2_SEND_ADDR = 0x82;

xQueueHandle rx_kbl_queue;

uint8_t dummy_data[8] = {1, 1, 2, 3, 4, 5, 6, 7};

twai_frame_t current_kbl_frame;
/* = {
    .header = {
        .dlc = 8,
        .ide = 0
    },
    .buffer = dummy_data,
    .buffer_len = sizeof(dummy_data)
};*/

int status;

esp_err_t kbl_init() {
    vTaskDelay(pdMS_TO_TICKS(5000));
    rx_kbl_queue = xQueueCreate(1, sizeof(twai_frame_t));
    assert(rx_kbl_queue);

    xTaskCreate(task_kbl_queries, "KBL Task", (8*1024), NULL, tskIDLE_PRIORITY + 3, NULL);

    return ESP_OK;
}

uint16_t kbl_getRPM(uint8_t data[8]) {
    return data[0] << 8 | data[1];
}

uint16_t kbl_getCurrent(uint8_t data[8]) {
    return data[3];
}

void task_kbl_queries(void *pvParameters) {
    // 0 = batch read 2
    // 1 = monitor1
    // 2 = monitor2

    for (;;) {
        for (int i = 0; i < 3; i++) {
            //ESP_LOGI("KBL", "Sending # %d", i);
            /*dummy_data[6]++;
            dummy_data[3] = 35;
            dummy_data[2]++;
            dummy_data[1]++;*/
            switch (i) {
                case 0:
                status = xQueueSend(tx_queue, &KBL_CCP_A2D_BATCH_READ2, 0);
                if (status == errQUEUE_FULL) break;
                xQueueReceive(rx_kbl_queue, &current_kbl_frame, portMAX_DELAY);
                current_kbl_frame.header.id = CCP_A2D_BATCH_READ2_SEND_ADDR;
                xQueueSend(tx_queue, &current_kbl_frame, portMAX_DELAY);
                // TODO do something!!
                break;
                case 1:
                status = xQueueSend(tx_queue, &KBL_CCP_MONITOR1, 0);
                if (status == errQUEUE_FULL) break;
                xQueueReceive(rx_kbl_queue, &current_kbl_frame, portMAX_DELAY);
                current_kbl_frame.header.id = CCP_MONITOR1_SEND_ADDR;
                xQueueSend(tx_queue, &current_kbl_frame, portMAX_DELAY);
                // TODO do something!!
                break;
                case 2:
                status = xQueueSend(tx_queue, &KBL_CCP_MONITOR2, 0);
                if (status == errQUEUE_FULL) break;
                xQueueReceive(rx_kbl_queue, &current_kbl_frame, portMAX_DELAY);
                current_kbl_frame.header.id = CCP_MONITOR2_SEND_ADDR;
                xQueueSend(tx_queue, &current_kbl_frame, portMAX_DELAY);
                // TODO do something!!
                break;
            }
        vTaskDelay(pdMS_TO_TICKS(50));
        }
    }
}