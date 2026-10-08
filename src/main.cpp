#include <Arduino.h>
#include <OneButton.h>

// 1. Cấu hình phần cứng theo đúng yêu cầu đề bài
#define LED1_PIN 2     // LED1 tích hợp trên devboard (GPIO 2)
#define LED2_PIN 4     // LED2 mắc ngoài trên test board (GPIO 4)
#define BUTTON_PIN 13 // Nút bấm ngoài riêng biệt (GPIO 13)

OneButton btn(BUTTON_PIN, true); // active Low (nối nút bấm vào GND)

// Biến trạng thái
int selectedLed = 1;     // 1: đang chọn LED1, 2: đang chọn LED2
bool led1State = LOW;
bool led2State = LOW;

bool isLongPressing = false; // Trạng thái có đang đè giữ nút hay không
unsigned long lastBlinkTime = 0;

// Khi single click: Bật/Tắt cái LED đang được điều khiển
void handleClick() {
  if (selectedLed == 1) {
    led1State = !led1State;
    digitalWrite(LED1_PIN, led1State);
  } else {
    led2State = !led2State;
    digitalWrite(LED2_PIN, led2State);
  }
}

// Khi double click: Chuyển chế độ điều khiển giữa hai LED (LED1 và LED2)
void handleDoubleClick() {
  if (selectedLed == 1) {
    selectedLed = 2;
  } else {
    selectedLed = 1;
  }
}

// Khi bắt đầu/đang giữ nút nhấn: Đánh dấu trạng thái giữ nút
void handleDuringLongPress() {
  isLongPressing = true;
}

// Khi buông nút nhấn ra: Tắt trạng thái giữ nút
void handleLongPressStop() {
  isLongPressing = false;
}

void setup() {
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Điện trở kéo lên nội cho nút bấm ngoài

  btn.setClickMs(150); // Phản hồi phím bấm nhạy hơn

  // Gán các hàm xử lý sự kiện
  btn.attachClick(handleClick);
  btn.attachDoubleClick(handleDoubleClick);
  btn.attachDuringLongPress(handleDuringLongPress);
  btn.attachLongPressStop(handleLongPressStop);
}

void loop() {
  btn.tick(); // Cập nhật trạng thái nút bấm liên tục

  // Khi giữ nút nhấn: Làm LED đang được điều khiển nhấp nháy 200ms một lần
  if (isLongPressing) {
    if (millis() - lastBlinkTime >= 200) {
      lastBlinkTime = millis();
      if (selectedLed == 1) {
        led1State = !led1State;
        digitalWrite(LED1_PIN, led1State);
      } else {
        led2State = !led2State;
        digitalWrite(LED2_PIN, led2State);
      }
    }
  }
}