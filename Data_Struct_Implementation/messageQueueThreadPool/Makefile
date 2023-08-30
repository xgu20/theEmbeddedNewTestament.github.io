CC=g++
CFLGAS=-Wall

# 链接器标志，例如，如果你使用了线程，可能需要加-lpthread
LDFLAGS = -lpthread

SRCS = main.cpp WorkerThread.cpp Fault.cpp

# 对于每一个.cpp源文件，.o文件是它的目标
OBJS = $(SRCS:.cpp=.o)

# 输出的可执行文件的名称
TARGET = threadpool

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f $(OBJS) $(TARGET)