# ESP32 OneButton LED Control Project (Task 4)

Dự án điều khiển trạng thái đèn LED trên vi điều khiển ESP32 DevKit V1 thông qua nút bấm BOOT tích hợp, sử dụng thư viện `OneButton` để xử lý sự kiện bấm và tự động khử rung phím (debounce).

---

## 1. Yêu cầu bài toán & Chức năng
- **Single Click (Bấm đơn 1 lần):** 
  - Bật hoặc Tắt LED tích hợp (đảo trạng thái ON/OFF).
  - Nếu LED đang ở chế độ nhấp nháy, bấm Single Click sẽ dừng nháy và đưa LED về trạng thái Bật/Tắt bình thường.
- **Double Click (Bấm đúp 2 lần):** 
  - Chuyển LED sang chế độ nhấp nháy liên tục (blink) với chu kỳ 200ms.
- **Tự động khử rung (Anti-bounce):** 
  - Sử dụng cơ chế lọc nhiễu tín hiệu nút bấm của thư viện `OneButton` để tránh nhận diện sai sự kiện do rung cơ học.

---

## 2. Sơ đồ phần cứng & Kết nối chân (Pin Mapping)
- **Bo mạch điều khiển:** ESP32 DevKit V1
- **Thiết bị ngoại vi:**
  - **LED tích hợp (Built-in LED):** Chân `GPIO 2`
  - **Nút bấm BOOT tích hợp:** Chân `GPIO 0` (Sử dụng trực tiếp nút BOOT có sẵn trên bo mạch, kích hoạt điện trở kéo lên nội `INPUT_PULLUP`).

---

## 3. Môi trường phát triển & Thư viện sử dụng
- **IDE / Framework:** Visual Studio Code kết hợp PlatformIO IDE extension (Framework Arduino).
- **Thư viện phụ thuộc (`lib_deps`):**
  - `mathertel/OneButton` @ ^2.0.0 (Dùng xử lý sự kiện nút bấm bất đồng bộ).

---

## 4. Giải thuật & Mã nguồn
Chương trình sử dụng cơ chế Non-blocking (không dùng `delay()` làm treo chip trong vòng lặp chính `loop()`) bằng cách so sánh thời gian thực với `millis()` để duy trì nhấp nháy LED:

```cpp
#include <Arduino.h>
#include <OneButton.h>

#define LED_PIN 2      // LED tích hợp GPIO 2
#define BUTTON_PIN 0   // Nút BOOT tích hợp GPIO 0

OneButton btn(BUTTON_PIN, true);

bool isBlinking = false;
bool ledState = LOW;
unsigned long lastBlinkTime = 0;

void handleClick() {
  isBlinking = false; 
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}

void handleDoubleClick() {
  isBlinking = !isBlinking;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  btn.setClickMs(150);

  btn.attachClick(handleClick);
  btn.attachDoubleClick(handleDoubleClick);
}

void loop() {
  btn.tick();

  if (isBlinking) {
    if (millis() - lastBlinkTime >= 200) {
      lastBlinkTime = millis();
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    }
  }
}