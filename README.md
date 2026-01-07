I. NÚT NHẤN (WAKE – VOL+ – VOL-)

👉 Nguyên lý:

1 chân GPIO

1 chân GND

ESP32 dùng INPUT_PULLUP

Nhấn = kéo GPIO xuống GND

✅ Cách cắm của bạn → ĐÚNG
    Your connection method → ​​CORRECT

Chức năng	GPIO	Chân còn lại
Wake	GPIO47	GND
Vol-	GPIO39	GND
Vol+	GPIO40	GND

| INMP441 | ESP32-S3 | Ý nghĩa      |
| ------- | -------- | ------------ |
| SD      | GPIO6    | Data         |
| SCK     | GPIO5    | Bit Clock    |
| WS / SM | GPIO4    | Word Select  |
| L/R     | GND      | Channel LEFT |
| GND     | GND      | Mass         |

IV. TỔNG KIỂM TRA XUNG ĐỘT GPIO ❗

| Chức năng | GPIO | Status
| --------- | ---- | ---------- |
| Wake      | 47   | OK         |
| Vol+      | 40   | OK         |
| Vol-      | 39   | OK         |
| OLED SDA  | 41   | OK         |
| OLED SCL  | 42   | OK         |
| MIC SD    | 6    | OK         |
| MIC SCK   | 5    | OK         |
| MIC WS    | 4    | OK         |


[Nút Wake / Vol]
        ↓
     ESP32-S3
        ↓
Mic INMP441 ── I2S ──► Xiaozhi AI
        ↑               ↓
OLED hiển thị      Audio / Lệnh

src/
├── main.cpp                 // entry point
│
├── core/
│   ├── App.h / App.cpp      // điều phối toàn bộ hệ thống
│   ├── Config.h             // GPIO, WiFi, AgentID
│
├── audio/
│   ├── AudioDevice.h        // class cha (interface)
│   ├── MicINMP441.h/.cpp    // mic
│   ├── SpeakerI2S.h/.cpp    // loa
│
├── ai/
│   ├── XiaoZhiClient.h/.cpp // websocket + protocol
│
├── input/
│   ├── Button.h/.cpp        // wake, vol+, vol-
│
├── display/
│   ├── DisplayBase.h        // class cha
│   ├── OLED_SSD1306.h/.cpp
│
└── utils/
    ├── Logger.h

II. SƠ ĐỒ KẾT NỐI TFT ST7735 (SPI – 3.3V)
| TFT ST7735 | ESP32-S3 | Ghi chú                |
| ---------- | -------- | ---------------------- |
| VCC        | 3V3      | ❌ Không cấp 5V         |
| GND        | GND      |                        |
| SCL / SCK  | GPIO42   | SPI Clock              |
| SDA / MOSI | GPIO41   | SPI Data               |
| CS         | GPIO10   | Chip Select            |
| DC         | GPIO9    | Data / Command         |
| RST        | GPIO8    | Reset                  |
| BL / LED   | 3V3      | Hoặc GPIO nếu muốn dim |

⚠️ Tên chân có thể in khác nhau (CS / SS / TFT_CS)

IX. BẠN ĐÃ CÓ GÌ SAU KIẾN TRÚC NÀY?

✅ Chatbot voice
✅ Wake button
✅ TTS
✅ Nhạc / radio / podcast (chỉ cần thêm AudioStream class)
✅ Automation (kế thừa CommandHandler)
✅ OLED hiển thị trạng thái
✅ Có thể port sang ESP-IDF dễ dàng

🎯 MỤC TIÊU BƯỚC NÀY

✅ ESP32 chỉ gửi audio khi có giọng nói
✅ Im lặng → không gửi gì cả
✅ Nhấn Wake → bật chế độ nghe
✅ Nói xong → tự dừng
✅ Chuẩn bị nền tảng cho:

Chatbot

Nhạc

Radio

Automation bằng giọng nói

I. KIẾN TRÚC MỞ RỘNG (KHÔNG PHÁ CŨ)

Thêm 1 module mới:

audio/
├── AudioDevice.h
├── MicINMP441.h / .cpp
├── SpeakerI2S.h / .cpp
├── VAD.h        ✅
├── VAD.cpp      ✅

II. NGUYÊN LÝ VAD (DỄ HIỂU)

Ta không dùng AI nặng, chỉ dùng RMS / Energy:

Tính độ lớn âm thanh

Nếu > ngưỡng → đang nói

Nếu < ngưỡng liên tục → im lặng

👉 Phù hợp ESP32-S3, chạy rất nhẹ.

V. KẾT QUẢ THỰC TẾ SAU BƯỚC NÀY 🔥

✅ Nhấn Wake
✅ Nói chuyện
✅ ESP32 chỉ gửi đúng đoạn có tiếng nói
✅ Ngừng nói → AI xử lý & trả lời
✅ Không bị spam audio
✅ Sẵn sàng chạy 24/7

IDLE
 ↓ (Wake)
LISTENING  🎤 (sóng âm)
 ↓ (im lặng)
THINKING   …
 ↓
SPEAKING   🔊 (AI nói)
 ↓
IDLE

✅ 7️⃣ Những gì bạn đã làm ĐÚNG

✔ Không nhét UI vào App
✔ Không xử lý audio trong display
✔ Có nền tảng mở rộng automation

Bạn đang làm đúng chuẩn firmware sản phẩm, không phải demo Arduino.

🚀 BƯỚC TIẾP THEO

Bạn muốn:

2️⃣ LISTENING → SPEAKING (AI trả lời)
3️⃣ LISTENING → IDLE khi im lặng (VAD)
4️⃣ Vẽ sóng âm trên màn hình

🚀 TRẠNG THÁI HIỆN TẠI (RẤT TỐT)

Hệ thống của bạn giờ đã:

✅ Thu mic INMP441 (16kHz)
✅ VAD phát hiện nói
✅ Gửi PCM16 thật lên Xiaozhi
✅ Nhận audio trả về
✅ Phát loa I2S
✅ TFT hiển thị trạng thái

Mình sẽ làm đúng kiểu embedded chuẩn, ít tốn RAM, dễ mở rộng.

🎯 MỤC TIÊU BƯỚC 4

LCD hiển thị rõ:

🟢 IDLE – chờ

🎤 LISTENING – đang nghe mic

🔊 SPEAKING – Xiaozhi đang trả lời

❌ ERROR / DISCONNECTED

UI đổi ngay khi state thay đổi

Không vẽ lại LCD liên tục (tránh flicker + reset)