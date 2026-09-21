# So sánh MQTT và HTTP

## 1. Điều kiện kiểm thử

- ESP32 được mô phỏng bằng Wokwi.
- Cảm biến DHT.
- Cùng dữ liệu nhiệt độ và độ ẩm được gửi qua MQTT và HTTP.
- Kiểm thử 20 mẫu dữ liệu từ sample_id 1 đến 20.
- MQTT sử dụng broker HiveMQ.
- HTTP Server được triển khai trên Render.

## 2. Kết quả độ tin cậy

| Giao thức | Số mẫu gửi | Số mẫu nhận | Số mẫu mất | Tỷ lệ thành công |
|---|---:|---:|---:|---:|
| MQTT | 20 | 20 | 0 | 100% |
| HTTP | 20 | 20 | 0 | 100% |

Trong lượt kiểm thử, cả MQTT và HTTP đều nhận đầy đủ 20/20 mẫu dữ liệu.

## 3. Kết quả tốc độ truyền

| Giao thức | Thời gian trung bình | Nhỏ nhất | Lớn nhất |
|---|---:|---:|---:|
| MQTT | 4.7 ms | 4 ms | 5 ms |
| HTTP | 8360.55 ms | 8097 ms | 8718 ms |

Trong điều kiện kiểm thử hiện tại, MQTT có thời gian truyền thấp hơn HTTP đáng kể.

HTTP cần gửi request đến server và chờ phản hồi nên thời gian xử lý lớn hơn, trong khi MQTT duy trì kết nối với broker và phù hợp với việc gửi dữ liệu cảm biến liên tục.

## 4. Kết luận

Về độ tin cậy, MQTT và HTTP đều đạt tỷ lệ truyền thành công 100% trong bộ kiểm thử 20 mẫu.

Về tốc độ, MQTT có thời gian truyền trung bình 4.7 ms, thấp hơn HTTP với 8360.55 ms trong môi trường kiểm thử của đề tài.

Kết quả cho thấy MQTT phù hợp hơn với trường hợp cần truyền dữ liệu IoT nhanh và liên tục. HTTP vẫn đảm bảo dữ liệu được truyền đầy đủ và phù hợp với mô hình giao tiếp request-response.