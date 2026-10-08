# ESP32 Dual LED Control via OneButton (Task 5)

Dự án mở rộng điều khiển 2 đèn LED (1 Built-in LED và 1 External LED) bằng duy nhất 1 nút bấm cắm ngoài thông qua thư viện `OneButton` trên vi điều khiển ESP32 DevKit V1.

---

## 1. Yêu cầu bài toán & Chức năng
- **Chuyển chế độ điều khiển (Double Click):** Bấm đúp 2 lần để chuyển đổi đối tượng LED đang tương tác (giữa LED 1 và LED 2).
- **Bật / Tắt LED (Single Click):** Bấm 1 lần để đảo trạng thái Bật/Tắt (ON/OFF) của LED hiện đang được chọn.
- **Nhấp nháy khi giữ nút (Long Press):** Đè giữ nút bấm sẽ làm LED đang được chọn nhấp nháy liên tục với chu kỳ 200ms/lần. Khi buông nút bấm ra sẽ dừng nháy.

---

## 2. Sơ đồ phần cứng & Kết nối chân (Pin Mapping)
- **LED 1 (Built-in LED):** Chân `GPIO 2`
- **LED 2 (External LED trên test board):** Chân `GPIO 4` (Nối qua điện trở 1kΩ xuống GND)
- **Nút bấm ngoài (External Push Button):** Chân `GPIO 13` (Nối chân còn lại xuống GND, kích hoạt `INPUT_PULLUP`)

---

## 3. Môi trường phát triển & Thư viện sử dụng
- **IDE:** Visual Studio Code + PlatformIO IDE Extension
- **Framework:** Arduino ESP32
- **Thư viện phụ thuộc (`lib_deps`):** `mathertel/OneButton` @ ^2.6.1