TARGET = banana
CC = gcc
CXX = g++

# CXXFLAGS = -Wall -O2 -I./src
# RUST_LIB = src/eval/release/eval_lib.a

# === ファイル探索 ===
# CPP_SRCS := $(shell find src -name '*.cpp')

CC_SRCS := $(shell find src -name '*.c')
CXX_SRCS := $(shell find src -name '*.cpp')

OBJS := $(CC_SRCS:.c=.o) $(CXX_SRCS:.cpp=.o)

# ===  rule ===
all: $(TARGET)

%.o: %.c
	$(CC) -c $< -o $@

%.o: %.cpp
	$(CXX) -c $< -o $@

# Rust静的ライブラリをビルド
# $(RUST_LIB):
# 	@echo "🦀 Building Rust static library..."
# 	cd rustlib && cargo build --release

# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# 最終リンク
$(TARGET): $(OBJS)
	$(CXX) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
# 	cd rustlib && cargo clean

test: $(TARGET)
	./$(TARGET) test_file/test.bnn

.PHONY: all clean