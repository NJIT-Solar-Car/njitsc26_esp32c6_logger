#include <Arduino.h>
#include <twai.h>

void task_send(void *pvParameters);
static bool twai_rx_cb(twai_node_handle_t handle, const twai_rx_done_event_data_t *edata, void *user_ctx);

static const char *TAG = "TWAITest";
static uint8_t recv_buff[8] = {0};
xQueueHandle rx_queue;
static uint8_t send_buf[8] = {0};

twai_node_handle_t node_hdl = NULL;
twai_onchip_node_config_t node_config = {
    .io_cfg = {
        .tx = GPIO_NUM_5,
        .rx = GPIO_NUM_4},
    .bit_timing = {.bitrate = 500000},
    .tx_queue_depth = 5,
    .flags = {.enable_loopback = true}};
twai_event_callbacks_t node_callbacks = {
    .on_rx_done = twai_rx_cb};

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello world!");

  esp_log_level_set("*", ESP_LOG_INFO);

  ESP_ERROR_CHECK(twai_new_node_onchip(&node_config, &node_hdl));
  ESP_ERROR_CHECK(twai_node_register_event_callbacks(node_hdl, &node_callbacks, NULL));
  ESP_ERROR_CHECK(twai_node_enable(node_hdl));

  rx_queue = xQueueCreate(5, sizeof(twai_frame_t));

  xTaskCreate(task_send, "Send Task", 4096, NULL, tskIDLE_PRIORITY, NULL);
}

void loop()
{
  // put your main code here, to run repeatedly:
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

    ESP_ERROR_CHECK(twai_node_transmit(node_hdl, &tx_msg, 0));
    ESP_ERROR_CHECK(twai_node_transmit_wait_all_done(node_hdl, -1));

    Serial.printf("Send: %03X | %02X %02X %02X %02X %02X %02X %02X %02X\r\n", tx_msg.header.id, send_buf[0], send_buf[1], send_buf[2], send_buf[3], send_buf[4], send_buf[5], send_buf[6], send_buf[7]);

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void task_recv(void *pvParameters) {
  for (;;) {
    Serial.printf("Recv: %03X | %02X %02X %02X %02X %02X %02X %02X %02X\r\n", rx_frame.header.id, recv_buff[0], recv_buff[1], recv_buff[2], recv_buff[3], recv_buff[4], recv_buff[5], recv_buff[6], recv_buff[7]);
  }
}

static bool twai_rx_cb(twai_node_handle_t handle, const twai_rx_done_event_data_t *edata, void *user_ctx)
{
  Serial.printf("Recv callback");
  rx_frame = {
      .buffer = recv_buff,
      .buffer_len = sizeof(recv_buff),
  };
  if (ESP_OK == twai_node_receive_from_isr(handle, &rx_frame))
  {
  }
  return false;
}