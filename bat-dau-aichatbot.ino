/****************************************************
 * ESP32-S3 VOICE CHATBOT XIAOZHI
 * MIC: INMP441
 * AMP: MAX98357
 * LCD: ST7735 1.8" 128x160
 ****************************************************/

#include <WiFi.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "driver/i2s.h"

/* ================= WIFI ================= */
const char* ssid     = "PixelCS";
const char* password = "PixelCS@Nhan";

/* ================= XIAOZHI ================= */
const char* WS_HOST = "ws.xiaozhi.ai";
const int   WS_PORT = 443;
const char* WS_PATH = "/agent";
const char* XIAOZHI_SHARE_CODE = "bCDOPYv5fL"; // 🔴 SỬA SHARE CODE CỦA BẠN

/* ================= LCD ST7735 ================= */
#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

/* ================= MIC INMP441 (I2S0) ================= */
#define MIC_BCLK 6
#define MIC_WS   5
#define MIC_DIN  4

/* ================= SPEAKER MAX98357 (I2S1) ================= */
#define SPK_BCLK 17
#define SPK_LRC  18
#define SPK_DOUT 16

WebSocketsClient ws;

/* ================= LCD FUNCTION ================= */
void lcd_show(String text) {
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(1);

  int maxCharsPerLine = 20;
  while (text.length() > 0) {
    tft.println(text.substring(0, maxCharsPerLine));
    text = text.substring(maxCharsPerLine);
  }
}

/* ================= MIC INIT ================= */
void mic_init() {
  i2s_config_t cfg = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .dma_buf_count = 4,
    .dma_buf_len = 512,
    .use_apll = false
  };

  i2s_pin_config_t pin = {
    .bck_io_num = MIC_BCLK,
    .ws_io_num = MIC_WS,
    .data_out_num = -1,
    .data_in_num = MIC_DIN
  };

  i2s_driver_install(I2S_NUM_0, &cfg, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin);
}

/* ================= SPEAKER INIT ================= */
void speaker_init() {
  i2s_config_t cfg = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = 24000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .dma_buf_count = 8,
    .dma_buf_len = 512,
    .use_apll = false
  };

  i2s_pin_config_t pin = {
    .bck_io_num = SPK_BCLK,
    .ws_io_num = SPK_LRC,
    .data_out_num = SPK_DOUT,
    .data_in_num = -1
  };

  i2s_driver_install(I2S_NUM_1, &cfg, 0, NULL);
  i2s_set_pin(I2S_NUM_1, &pin);
}

/* ================= WEBSOCKET EVENT ================= */
void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {

  if (type == WStype_CONNECTED) {
    StaticJsonDocument<256> doc;
    doc["type"] = "auth";
    doc["share_code"] = XIAOZHI_SHARE_CODE;

    String msg;
    serializeJson(doc, msg);
    ws.sendTXT(msg);

    lcd_show("XIAOZHI READY\nSay something...");
  }

  else if (type == WStype_TEXT) {
    String reply = (char*)payload;
    lcd_show(reply);
  }

  else if (type == WStype_BIN) {
    size_t written;
    i2s_write(I2S_NUM_1, payload, length, &written, portMAX_DELAY);
  }
}

/* ================= SEND MIC AUDIO ================= */
void send_audio() {
  static int16_t buffer[512];
  size_t bytes_read;

  i2s_read(I2S_NUM_0, buffer, sizeof(buffer), &bytes_read, portMAX_DELAY);
  ws.sendBIN((uint8_t*)buffer, bytes_read);
}

/* ================= SETUP ================= */
void setup() {
  Serial.begin(115200);

  tft.initR(INITR_BLACKTAB);
  lcd_show("BOOTING...");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }

  lcd_show("WIFI OK");

  mic_init();
  speaker_init();

  ws.beginSSL(WS_HOST, WS_PORT, WS_PATH);
  ws.onEvent(webSocketEvent);
}

/* ================= LOOP ================= */
void loop() {
  ws.loop();
  send_audio();
}
