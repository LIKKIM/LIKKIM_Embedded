# 编译器
CC = arm-none-linux-gnueabihf-gcc

# 编译选项
CFLAGS = -Wall -I../ -I../algo

# 目标文件
OBJS = usart1.o CalControlPara.o algo_data_comm.o

# 默认目标
all: $(OBJS)

# 编译规则
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理规则
clean:
	rm -f $(OBJS)
