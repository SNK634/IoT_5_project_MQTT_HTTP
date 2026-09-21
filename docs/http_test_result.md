# HTTP Test Result

## Kết quả kiểm thử API

- POST dữ liệu hợp lệ: HTTP 201 - Success
- POST thiếu dữ liệu bắt buộc: HTTP 400 - Error
- GET /data: lấy dữ liệu thành công
- DELETE /data: xóa dữ liệu thành công

## Kiểm thử 20 mẫu

| Chỉ số | Kết quả |
|---|---:|
| Số mẫu gửi | 20 |
| Số mẫu nhận | 20 |
| Số mẫu mất | 0 |
| Tỷ lệ thành công | 100% |

Các mẫu từ `sample_id 1` đến `20` đều được HTTP Server ghi nhận đầy đủ.

Dữ liệu chi tiết:

`server/data/http_test_20.csv`