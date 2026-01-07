#include "XiaozhiClient.h"
#include "Config.h"
#include "Base64.h"
#include "AudioPlayer.h"

#include <WebSocketsClient.h>
#include <ArduinoJson.h>

static WebSocketsClient ws;

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
      if (deserializeJson(doc, payload)) return;

      /* ===== TEXT ===== */
      if (doc["type"] == "text") {
        Serial.print("Xiaozhi: ");
        Serial.println(doc["data"].as<String>());
      }

      /* ===== AUDIO ===== */
      if (doc["type"] == "audio") {
        const char* b64 = doc["data"];
        size_t outLen;
        uint8_t* pcm = base64Decode(b64, strlen(b64), &outLen);
        AudioPlayer::playPCM((int16_t*)pcm, outLen / 2);
        free(pcm);
      }
      break;
    }

    default:
      break;
  }
}

void XiaozhiClient::init() {

  ws.beginSSL(
    XIAOZHI_HOST,
    XIAOZHI_PORT,
    XIAOZHI_PATH
  );

  ws.onEvent(onEvent);

  ws.setReconnectInterval(3000);
}

void XiaozhiClient::loop() {
  ws.loop();
}

void XiaozhiClient::sendAudio(int16_t* pcm, size_t len) {
  String b64 = base64Encode((uint8_t*)pcm, len * 2);

  DynamicJsonDocument doc(2048);
  doc["type"] = "audio";
  doc["data"] = b64;

  String msg;
  serializeJson(doc, msg);
  ws.sendTXT(msg);
}
