#include "XiaozhiClient.h"
#include "Config.h"
#include "Base64.h"
#include "AudioPlayer.h"

#include <WebSocketsClient.h>
#include <ArduinoJson.h>

/* ================= WEBSOCKET ================= */
WebSocketsClient XiaozhiClient::ws;
bool XiaozhiClient::speaking = false;

/* ================= EVENT HANDLER ================= */
// 🔹 thêm biến static
String XiaozhiClient::lastText = "";

void XiaozhiClient::onEvent(WStype_t type, uint8_t* payload, size_t length) {
    switch (type) {
        case WStype_CONNECTED:
            Serial.println("[XIAOZHI] Connected MCP");
            break;
        case WStype_DISCONNECTED:
            Serial.println("[XIAOZHI] Disconnected");
            speaking = false;
            break;
        case WStype_TEXT:
        case WStype_BIN: {
            DynamicJsonDocument doc(8192);
            DeserializationError err = deserializeJson(doc, payload);
            if (err) return;

            if (!doc.containsKey("type")) return;

            if (doc["type"] == "text") {
               String txt = doc["data"].as<String>();
               Serial.print("Xiaozhi: "); Serial.println(txt);
                // 🔹 lưu text mới
               lastText = txt;
            }

            if (doc["type"] == "audio") {
                speaking = true;
                const char* b64 = doc["data"];
                if (!b64) return;

                size_t outLen = 0;
                uint8_t* pcm = base64Decode(b64, strlen(b64), &outLen);
                if (pcm && outLen > 0) {
                    AudioPlayer::playPCM((int16_t*)pcm, outLen / 2);
                    free(pcm);
                }
                speaking = false;  // TTS đã phát xong
            }
            break;
        }
        default: break;
    }
}

/* ================= INIT ================= */
void XiaozhiClient::init() {

  ws.beginSSL(XIAOZHI_HOST,XIAOZHI_PORT,XIAOZHI_PATH);
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

    String msg; serializeJson(doc, msg);
    ws.sendTXT(msg);
}

/* ================= END AUDIO ================= */
void XiaozhiClient::endAudio() {
    DynamicJsonDocument doc(64);
    doc["type"] = "audio_end";
    String msg; serializeJson(doc, msg);
    ws.sendTXT(msg);
    Serial.println("[XIAOZHI] Audio end sent");
}