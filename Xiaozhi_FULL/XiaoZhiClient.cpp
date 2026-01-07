#include "XiaozhiClient.h"
#include "Config.h"
#include "Base64.h"
#include "AudioPlayer.h"

#include <WebSocketsClient.h>
#include <ArduinoJson.h>

/* ================= WEBSOCKET ================= */

WebSocketsClient XiaozhiClient::ws;

/* ================= EVENT HANDLER ================= */
static void onEvent(WStype_t type, uint8_t* payload, size_t length) {

  switch (type) {

    case WStype_CONNECTED:
      Serial.println("[XIAOZHI] Connected MCP");
      break;

    case WStype_DISCONNECTED:
      Serial.println("[XIAOZHI] Disconnected");
      break;

    case WStype_TEXT: {
      DynamicJsonDocument doc(8192);

      DeserializationError err = deserializeJson(doc, payload);
      if (err) {
        Serial.println("[XIAOZHI] JSON parse error");
        return;
      }

      if (!doc.containsKey("type")) return;

      /* ===== TEXT RESPONSE ===== */
      if (doc["type"] == "text") {
        Serial.print("Xiaozhi: ");
        Serial.println(doc["data"].as<String>());
      }

      /* ===== AUDIO RESPONSE ===== */
      if (doc["type"] == "audio") {
        Serial.println("[XIAOZHI] Audio packet received");

        const char* b64 = doc["data"];
        if (!b64) return;

        size_t outLen = 0;
        uint8_t* pcm = base64Decode(b64, strlen(b64), &outLen);

        if (pcm && outLen > 0) {
          AudioPlayer::playPCM((int16_t*)pcm, outLen / 2);
          free(pcm);
        } else {
          Serial.println("[XIAOZHI] Audio decode failed");
        }
      }

      break;
    }

    default:
      break;
  }
}

/* ================= INIT ================= */
void XiaozhiClient::init() {

  ws.beginSSL(
    XIAOZHI_HOST,
    XIAOZHI_PORT,
    XIAOZHI_PATH
  );

  ws.onEvent(onEvent);
  ws.setReconnectInterval(3000);

  Serial.println("[XIAOZHI] Init done");
}

/* ================= LOOP ================= */
void XiaozhiClient::loop() {
  ws.loop();
}

/* ================= SEND AUDIO ================= */
void XiaozhiClient::sendAudio(int16_t* pcm, size_t samples) {

  if (!pcm || samples == 0) return;

  String b64 = base64Encode((uint8_t*)pcm, samples * 2);

  DynamicJsonDocument doc(4096);
  doc["type"] = "audio";
  doc["format"] = "pcm16";
  doc["sample_rate"] = 16000;
  doc["channels"] = 1;
  doc["data"] = b64;

  String msg;
  serializeJson(doc, msg);

  ws.sendTXT(msg);
}

/* ================= END AUDIO (BẮT BUỘC) ================= */
void XiaozhiClient::endAudio() {

  DynamicJsonDocument doc(64);
  doc["type"] = "audio_end";

  String msg;
  serializeJson(doc, msg);

  ws.sendTXT(msg);

  Serial.println("[XIAOZHI] Audio end sent");
}
// ÁCH TEST NHANH (KHÔNG CẦN MIC)
void XiaozhiClient::testSpeak() {
  Serial.println("[TEST] Send fake audio");

  // Tạo audio giả (im lặng 0.5s)
  static int16_t dummy[8000] = {0};

  sendAudio(dummy, 8000);
  endAudio();
}