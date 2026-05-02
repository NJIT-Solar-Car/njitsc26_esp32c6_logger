#include "esp_twai.h"
#include "esp_twai_onchip.h"
#include "esp_twai_types.h"

twai_node_handle_t node_hdl = NULL;
twai_onchip_node_config_t node_config = {
    .io_cfg = {
        .tx = GPIO_NUM_5,
        .rx = GPIO_NUM_4
    },
    .bit_timing = {
        .bitrate = 500000
    },
    .tx_queue_depth = 5
};

