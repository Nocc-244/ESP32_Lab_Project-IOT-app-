#include <Arduino.h>
#include <OneButton.h>

#define LED_PIN 2      // LED tích hợp trên bo ESP32 (GPIO 2)
#define BUTTON_PIN 0   // Nút BOOT tích hợp sẵn trên bo ESP32 (GPIO 0)

OneButton btn(BUTTON_PIN, true);

bool isBlinking = false; // Trạng thái có đang nhấp nháy hay không
bool ledState = LOW;
unsigned long lastBlinkTime = 0;

// Single Click: Bật / Tắt LED (khi không ở chế độ nháy)
void handleClick() {
  isBlinking = false; // Tắt chế độ nháy
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}

// Double Click: Bật / Tắt chế độ nhấp nháy LED
void handleDoubleClick() {
  isBlinking = !isBlinking;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Bật điện trở kéo lên nội cho GPIO 0
  
  btn.setClickMs(150); // Rút ngắn thời gian chờ Double Click để nhạy hơn

  btn.attachClick(handleClick);
  btn.attachDoubleClick(handleDoubleClick);
}

void loop() {
  btn.tick(); // Cập nhật trạng thái nút bấm liên tục

  // Nếu đang ở chế độ nháy, nhấp nháy LED mỗi 200ms
  if (isBlinking) {
    if (millis() - lastBlinkTime >= 200) {
      lastBlinkTime = millis();
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    }
  }
}