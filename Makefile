BUILD_DIR := build
SRC_DIR := src
LIB_DIR := lib/SFML-2.5.1/lib
INC_DIR := lib/SFML-2.5.1/include
OBJ_DIR := $(BUILD_DIR)/obj

TARGET := $(BUILD_DIR)/NES_EMULATOR
SRC_LIST := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_LIST := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o, $(SRC_LIST))

CC := g++
CFLAGS := -Wall
CPPFLAGS := -MMD 
LDFLAGS := -lsfml-graphics -lsfml-window -lsfml-system

all: $(TARGET)

$(TARGET) : $(OBJ_LIST) | $(BUILD_DIR)
	$(CC) $^ -o $@ -L$(LIB_DIR) $(LDFLAGS) -Wl,-rpath=$(LIB_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR) $(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean