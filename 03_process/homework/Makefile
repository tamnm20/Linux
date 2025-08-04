# Tìm tất cả các file .c trong thư mục hiện tại
SOURCES := $(wildcard *.c)

# Chuyển đổi mỗi file .c thành tên file thực thi (bỏ phần .c)
TARGETS := $(SOURCES:.c=)

# Mặc định khi gõ `make`, sẽ build tất cả
all: clean $(TARGETS)
	./B4

# Quy tắc để build từng file .c thành file thực thi
%: %.c
	gcc $< -o $@

# Lệnh dọn sạch các file thực thi
clean:
	rm -rf $(TARGETS) log/hello.txt file.txt

