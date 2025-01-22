# 定义编译器和编译选项
# CC = arm-none-eabi-gcc
# AR = arm-none-eabi-ar
CC = arm-linux-gnueabihf-gcc
AR = arm-linux-gnueabihf-ar
CFLAGS = -I.

# 定义库路径和库名
LIB_DIR = .
LIBS = -lwallet_algo -L../build/rust-builds -lrust_c

# 默认目标
all: test_main

# 编译可执行文件
test_main: test_main.o
	$(CC) $(CFLAGS) $< -L$(LIB_DIR) $(LIBS) -o $@ 
#--specs=nosys.specs

test_main.o: test_main.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成文件
clean:
	rm -f test_main.o test_main
