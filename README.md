Xây dựng máy tính có thể thực hiện cộng trừ nhân chia số nguyên. Yêu cầu:
- Giao diện giống máy tính trên windows.
- Sử dụng thư viện sqlite để lưu trữ lịch sử tính toán (Có thể coi lại khi khởi động lại ứng dụng)
- Sử dụng Qt/QML

Về project này: 
Thực hiện các phép tính số nguyên:
Cộng (+)
Trừ (-)
Nhân (×)
Chia (÷)
Note: Ở đây là thao tác trên số nguyên nên không tạo nút "." thập phân, và kết quả trả về ở phía chia là dạng lấy số nguyên chứ không phải số thực. Nếu anh cần chỉnh lại logic toán hay có yêu cầu gì thêm thì em sẽ fix theo yêu cầu ạ.
Hỗ trợ các thao tác:
CE (Clear Entry)
C (Clear All)
Backspace (⌫)
Đổi dấu (±)
Hiển thị kết quả theo thời gian thực trên giao diện QML
Lưu lịch sử phép tính vào cơ sở dữ liệu SQLite
Tự động tải lại lịch sử khi khởi động lại ứng dụng
Hiển thị tối đa 50 phép tính gần nhất

Cách chạy: clone project về, sử dụng QT Creator mở file CMakeLists.txt 
