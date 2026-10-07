# Báo cáo nâng cấp đồ án MQTT và HTTP

## 1. Mục tiêu

Đồ án được nâng cấp để mô phỏng việc truyền dữ liệu cảm biến nhiệt độ và độ ẩm bằng hai giao thức MQTT và HTTP.

Phần MQTT dùng mô hình publish/subscribe để gửi dữ liệu realtime qua broker HiveMQ. Phần HTTP dùng Node.js server để nhận dữ liệu qua API và lưu vào file JSON.

## 2. MQTT

Dữ liệu MQTT được chia thành 2 topic:

- iot/demo/temperature
- iot/demo/humidity

Điều kiện cảnh báo:

- Nhiệt độ > 45°C: cảnh báo nóng
- Độ ẩm < 50%: cảnh báo khô

Kết quả: MQTTBox nhận được dữ liệu đúng topic và hiển thị được trạng thái cảnh báo.

## 3. HTTP

HTTP Server chạy bằng Node.js/Express tại port 3000.

Các API đã kiểm thử:

- GET /
- GET /data
- POST /data

Kết quả: server nhận dữ liệu bằng POST, hiển thị trên terminal và lưu vào server/data/http_data.json.

## 4. So sánh

MQTT phù hợp hơn cho dữ liệu cảm biến realtime, gửi liên tục và nhẹ tài nguyên.

HTTP phù hợp cho API, lưu trữ dữ liệu và kiểm thử bằng trình duyệt hoặc công cụ gửi request.

## 5. Kết luận

Sau khi nâng cấp, đồ án có đủ hai hướng truyền dữ liệu: MQTT để truyền realtime và HTTP để nhận/lưu dữ liệu. Việc thêm topic riêng và cảnh báo giúp đồ án gần với mô hình IoT thực tế hơn.
