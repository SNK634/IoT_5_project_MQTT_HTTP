@'
# IoT MQTT & HTTP - DHT11/DHT22 Data Transmission

## 1. Giới thiệu

Đồ án mô phỏng hệ thống IoT thu thập dữ liệu nhiệt độ và độ ẩm từ cảm biến DHT11/DHT22. Dữ liệu được truyền bằng hai giao thức phổ biến là MQTT và HTTP để kiểm thử, lưu trữ và so sánh khả năng ứng dụng trong hệ thống IoT.

Mục tiêu của đồ án:

- Gửi dữ liệu nhiệt độ và độ ẩm bằng MQTT.
- Chia dữ liệu MQTT thành 2 topic riêng.
- Thêm cảnh báo khi nhiệt độ hoặc độ ẩm vượt ngưỡng.
- Xây dựng HTTP Server bằng Node.js/Express.
- Nhận dữ liệu qua API `POST /data`.
- Lưu dữ liệu HTTP vào file JSON.
- So sánh MQTT và HTTP trong bài toán IoT.

## 2. Công nghệ sử dụng

- ESP32 / Wokwi
- DHT11/DHT22
- Google Colab
- MQTTBox
- HiveMQ Public Broker
- Node.js
- Express.js
- JSON
- GitHub

## 3. Kiến trúc hệ thống

```text
DHT11/DHT22 / Google Colab giả lập cảm biến
        |
        |---------------- MQTT ----------------|
        |                                      |
        v                                      v
  HiveMQ Broker                         MQTTBox Subscriber

        |---------------- HTTP ----------------|
        v
 Node.js HTTP Server
        |
        v
 server/data/http_data.json

 4. Chức năng MQTT
MQTT được sử dụng để truyền dữ liệu cảm biến theo mô hình Publish/Subscribe.
Broker:
broker.hivemq.com
Port: 1883

Các topic sử dụng:
iot/demo/temperature  -> gửi dữ liệu nhiệt độ
iot/demo/humidity     -> gửi dữ liệu độ ẩm

Điều kiện cảnh báo:
Nhiệt độ > 45°C  -> Cảnh báo nóng
Độ ẩm < 50%      -> Cảnh báo khô

Ví dụ dữ liệu MQTT:
NHIET DO: 55 C | CANH BAO NONG | Mau: 7
DO AM: 42 % | CANH BAO KHO | Mau: 7

File code MQTT:
docs/colab_mqtt_2_topics_alert.py

5. Chức năng HTTP
HTTP Server được xây dựng bằng Node.js và Express.js.
Các API chính:
GET  /       -> kiểm tra server hoạt động
GET  /data   -> xem dữ liệu đã nhận
POST /data   -> gửi dữ liệu cảm biến lên server
DELETE /data -> xóa dữ liệu đã lưu