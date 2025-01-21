# 编译选项
CFLAGS = -I./Hardware -I./algo -Wall
# LIBS = ./algo/libwallet_algo.a ./algo/libnetwork.a -lpthread

# 目标文件
TARGET = libusart_program.a
SRCS = Hardware/usart1.c Hardware/CalControlPara.c Hardware/algo_data_comm.c
OBJS = $(SRCS:.c=.o)

# 默认规则
KLKKLM_ALL: $(TARGET)

# 生成目标可执行文件
$(TARGET): $(OBJS) ./algo/libwallet_algo.a ./algo/libnetwork.a
	$(AR) -rsv $@ $(OBJS) 

# 编译 .c 文件生成 .o 文件
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 为静态库生成索引
./algo/libwallet_algo.a:
	$(RANLIB) $@

./algo/libnetwork.a:
	$(RANLIB) $@

# 清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET)
