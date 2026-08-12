# ESP32 DHT11 MQTT vs HTTP Comparison
Tên project Git; IoT_5_project_MQTT_HTTP
## Đề tài

Gửi dữ liệu cảm biến nhiệt độ và độ ẩm DHT11 từ ESP32 lên server bằng 2 giao thức MQTT và HTTP, sau đó so sánh tốc độ và độ tin cậy truyền dữ liệu.

## Thành viên

- Tâm: ESP32 Wokwi, đọc DHT11, gửi MQTT/HTTP, quản lý source GitHub
- An: MQTT Broker, MQTT Subscriber, kiểm thử MQTT
- Tuấn: HTTP Server, API nhận dữ liệu HTTP
- Bích: Kiểm thử, thống kê kết quả, báo cáo

## Công nghệ sử dụng

- ESP32
- DHT11
- Wokwi
- MQTT
- HTTP
- Node.js
- GitHub

## Cấu trúc thư mục

```text
wokwi/     Code ESP32 chạy trên Wokwi
server/    Server HTTP và MQTT subscriber
results/   File kết quả kiểm thử
docs/      Tài liệu, kế hoạch test, ảnh minh chứng
report/    Báo cáo cuối cùng
Link project trên Wokwi
https://wokwi.com/projects/472153519659552769


## Phần setup của Tâm: ESP32 + DHT11 + MQTT trên Wokwi

### 1. Môi trường sử dụng

Phần ESP32 được thực hiện trên trình giả lập Wokwi, quản lý source code bằng VS Code và GitHub.

Công cụ sử dụng:

- Wokwi: mô phỏng ESP32 và cảm biến DHT
- VS Code: lưu source code và quản lý project
- GitHub: quản lý mã nguồn nhóm
- MQTTX: kiểm tra dữ liệu MQTT được ESP32 gửi lên broker
- MQTT Broker: broker.hivemq.com

### 2. Các file chính

Trong project có thư mục `wokwi/` gồm các file:

```text
wokwi/
├── sketch.ino
├── diagram.json
└── libraries.txt

Ý nghĩa từng file:

sketch.ino: chứa code ESP32 đọc dữ liệu nhiệt độ, độ ẩm và gửi dữ liệu bằng MQTT.
diagram.json: mô tả sơ đồ kết nối giữa ESP32 và cảm biến DHT trên Wokwi.
libraries.txt: khai báo các thư viện cần dùng trong Wokwi.
3. Thư viện sử dụng

Các thư viện được thêm trong Wokwi:

DHT sensor library
Adafruit Unified Sensor
PubSubClient
ArduinoJson

Ý nghĩa:

DHT sensor library: đọc dữ liệu nhiệt độ và độ ẩm từ cảm biến DHT.
Adafruit Unified Sensor: thư viện phụ trợ cho cảm biến DHT.
PubSubClient: dùng để ESP32 publish dữ liệu lên MQTT broker.
ArduinoJson: tạo dữ liệu dạng JSON trước khi gửi đi.
4. Cấu hình MQTT

ESP32 gửi dữ liệu MQTT đến broker công khai:

MQTT Broker: broker.hivemq.com
Port: 1883
Topic: esp32/dht11/data/tam
QoS: 0

Dữ liệu gửi lên MQTT có dạng JSON:

{
  "packet_id": 4,
  "temperature": 30,
  "humidity": 70,
  "protocol": "MQTT",
  "send_time": 23086
}

Ý nghĩa dữ liệu:

packet_id: số thứ tự gói dữ liệu được ESP32 gửi đi.
temperature: giá trị nhiệt độ đọc từ cảm biến.
humidity: giá trị độ ẩm đọc từ cảm biến.
protocol: giao thức đang sử dụng, ở đây là MQTT.
send_time: thời điểm gửi dữ liệu, tính theo thời gian chạy của ESP32 bằng hàm millis().
5. Quy trình thực hiện

Các bước đã thực hiện:

Tạo project ESP32 mới trên Wokwi.
Thêm cảm biến DHT vào sơ đồ mô phỏng.
Kết nối cảm biến DHT với ESP32:
VCC nối với 3V3
GND nối với GND
DATA nối với GPIO 15
Viết code ESP32 trong file sketch.ino.

Cấu hình WiFi Wokwi bằng:

const char* WIFI_SSID = "Wokwi-GUEST";
const char* WIFI_PASSWORD = "";

Cấu hình MQTT broker:

const char* MQTT_SERVER = "broker.hivemq.com";
const int MQTT_PORT = 1883;
const char* MQTT_TOPIC = "esp32/dht11/data/tam";
Thêm thư viện cần thiết trong libraries.txt.
Chạy mô phỏng trên Wokwi.
Dùng MQTTX để kết nối đến broker.hivemq.com.
Subscribe topic esp32/dht11/data/tam.
Kiểm tra MQTTX nhận được dữ liệu JSON từ ESP32.
6. Kết quả đạt được

Sau khi chạy mô phỏng thành công, MQTTX đã nhận được dữ liệu từ ESP32 thông qua topic:

esp32/dht11/data/tam

Ví dụ dữ liệu nhận được:

{
  "packet_id": 4,
  "temperature": 30,
  "humidity": 70,
  "protocol": "MQTT",
  "send_time": 23086
}

Điều này chứng minh rằng ESP32 trên Wokwi đã đọc được dữ liệu nhiệt độ và độ ẩm từ cảm biến DHT, sau đó gửi dữ liệu thành công lên MQTT Broker thông qua giao thức MQTT.

7. Ý nghĩa kết quả

Kết quả trên cho thấy luồng truyền dữ liệu MQTT hoạt động đúng:

ESP32 + DHT trên Wokwi
        ↓
Đọc nhiệt độ và độ ẩm
        ↓
Đóng gói dữ liệu thành JSON
        ↓
Publish lên MQTT Broker
        ↓
MQTTX subscribe topic và nhận dữ liệu

Phần này là cơ sở để nhóm tiếp tục so sánh MQTT với HTTP về:

tốc độ truyền dữ liệu
số gói gửi thành công
số gói lỗi
độ tin cậy khi truyền dữ liệu cảm biến

Ghi ngắn gọn hơn thì bạn có thể dùng đoạn này:

```markdown
## Setup ESP32 MQTT trên Wokwi

Tâm phụ trách tạo mô phỏng ESP32 và cảm biến DHT trên Wokwi. ESP32 đọc dữ liệu nhiệt độ và độ ẩm từ cảm biến DHT, sau đó đóng gói dữ liệu thành JSON và gửi lên MQTT Broker `broker.hivemq.com` thông qua topic `esp32/dht11/data/tam`.

Project sử dụng các thư viện: `DHT sensor library`, `Adafruit Unified Sensor`, `PubSubClient` và `ArduinoJson`.

Dữ liệu MQTT được kiểm tra bằng phần mềm MQTTX. Sau khi MQTTX subscribe topic `esp32/dht11/data/tam`, hệ thống nhận được dữ liệu dạng JSON:

```json
{
  "packet_id": 4,
  "temperature": 30,
  "humidity": 70,
  "protocol": "MQTT",
  "send_time": 23086
}

Kết quả này chứng minh ESP32 đã gửi dữ liệu cảm biến lên MQTT Broker thành công. Đây là phần nền tảng để nhóm tiếp tục triển khai giao thức HTTP và so sánh tốc độ, độ tin cậy giữa MQTT và HTTP.