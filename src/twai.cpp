#include <twai.h>

static uint8_t recv_buff[8] = {0};
xQueueHandle rx_queue;
twai_frame_t rx_frame;
static uint8_t send_buf[8] = {0};
static const char *TAG = "drv_TWAI";

twai_node_handle_t node_hdl = NULL;
twai_onchip_node_config_t node_config = {
    .io_cfg = {
        .tx = GPIO_NUM_5,
        .rx = GPIO_NUM_4},
    .bit_timing = {.bitrate = 500000},
    .tx_queue_depth = 5,
    .flags = {
      .enable_self_test = 1,
      .enable_loopback = 1
    }};
twai_event_callbacks_t node_callbacks = {
    .on_rx_done = twai_rx_cb};


esp_err_t twai_init() {
  ESP_ERROR_CHECK(twai_new_node_onchip(&node_config, &node_hdl));
  ESP_ERROR_CHECK(twai_node_register_event_callbacks(node_hdl, &node_callbacks, NULL));
  ESP_ERROR_CHECK(twai_node_enable(node_hdl));

  rx_queue = xQueueCreate(node_config.tx_queue_depth, sizeof(twai_frame_t));

  xTaskCreate(task_send, "Send Task", 4096, NULL, tskIDLE_PRIORITY, NULL);
  xTaskCreate(task_recv, "Recv Task", 4096, NULL, tskIDLE_PRIORITY + 1, NULL);
  xTaskCreate(task_twai_status, "Stats Task", 4096, NULL, tskIDLE_PRIORITY + 2, NULL);

  return ESP_OK;
}

void task_send(void *pvParameters)
{
  for (;;)
  {
    send_buf[7]++;

    twai_frame_t tx_msg = {
        .header = {
            .id = 0x123,
            .ide = false},
        .buffer = send_buf,
        .buffer_len = sizeof(send_buf)};

    ESP_ERROR_CHECK(twai_node_transmit(node_hdl, &tx_msg, -1));
    ESP_ERROR_CHECK(twai_node_transmit_wait_all_done(node_hdl, -1));

    ESP_LOGI(TAG, "Send: %03X | %02X %02X %02X %02X %02X %02X %02X %02X", tx_msg.header.id, send_buf[0], send_buf[1], send_buf[2], send_buf[3], send_buf[4], send_buf[5], send_buf[6], send_buf[7]);

    // vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void task_recv(void *pvParameters) {
  for (;;) {
    xQueueReceive(rx_queue, &rx_frame, portMAX_DELAY);
    ESP_LOGI(TAG, "Recv: %03X | %02X %02X %02X %02X %02X %02X %02X %02X", rx_frame.header.id, recv_buff[0], recv_buff[1], recv_buff[2], recv_buff[3], recv_buff[4], recv_buff[5], recv_buff[6], recv_buff[7]);
  }
}

void task_twai_status(void *pvParameters) {
  twai_node_status_t node_status;
  twai_node_record_t node_records;
  twai_error_state_t last_error_state = TWAI_ERROR_ACTIVE;
  for (;;) {
    twai_node_get_info(node_hdl, &node_status, &node_records);
    if (node_status.state != last_error_state)  {
      last_error_state = node_status.state;
      switch (node_status.state) {
        case TWAI_ERROR_ACTIVE:
          ESP_LOGI(TAG, "TWAI active");
          break;
        case TWAI_ERROR_WARNING:
          ESP_LOGW(TAG, "TWAI in Error Warning state");
          break;
        case TWAI_ERROR_PASSIVE:
          ESP_LOGE(TAG, "TWAI in Error Passive state!");
          break;
        case TWAI_ERROR_BUS_OFF:
          ESP_LOGE(TAG, "TWAI in Bus Off state!");
          break;
      }
    }

    vTaskDelay(pdMS_TO_TICKS(2000));

  }
}

static bool twai_rx_cb(twai_node_handle_t handle, const twai_rx_done_event_data_t *edata, void *user_ctx)
{
  twai_frame_t rx_frame_to_push = {
      .buffer = recv_buff,
      .buffer_len = sizeof(recv_buff),
  };
  if (ESP_OK == twai_node_receive_from_isr(handle, &rx_frame_to_push))
  {
    xQueueSendFromISR(rx_queue, &rx_frame_to_push, NULL);
  }
  return false;
}