#pragma once
#include <Arduino.h>


/* ================= WIFI ================= */
#define WIFI_SSID   "PixelCS"
#define WIFI_PASS   "PixelCS@Nhan"

/* ================= XIAOZHI ================= */

#define XIAOZHI_HOST "api.xiaozhi.me"
#define XIAOZHI_PORT 443

#define XIAOZHI_PATH "/mcp/?token=eyJhbGciOiJFUzI1NiIsInR5cCI6IkpXVCJ9.eyJ1c2VySWQiOjcxODc4NiwiYWdlbnRJZCI6MTIyMDYwNywiZW5kcG9pbnRJZCI6ImFnZW50XzEyMjA2MDciLCJwdXJwb3NlIjoibWNwLWVuZHBvaW50IiwiaWF0IjoxNzY3NzgxODE2LCJleHAiOjE3OTkzMzk0MTZ9.pplAnV0gnmt1ZuO6KavKZfQoDuq8IyXudmc4L6H4zPLvMD5SeSiDnIA6uvxI6qPV8D52YIiuBlrrVxfjTWOrAg"


/* ================= APP STATE ================= */
enum class AppState {
  IDLE,
  LISTENING,
  SPEAKING
};

/* ================= BUTTON ================= */
#define PIN_WAKE    47
#define PIN_VOL_UP  40
#define PIN_VOL_DN  39

/* ================= TFT ST7735 ================= */
#define TFT_SCK   42
#define TFT_MOSI  41
#define TFT_CS    10
#define TFT_DC    9
#define TFT_RST   8

/* ================= MIC INMP441 ================= */
#define MIC_SD   6
#define MIC_SCK  5
#define MIC_WS   4

/* ================= AUDIO ================= */
#define AUDIO_BUF   512
#define SAMPLE_RATE 16000
