# ========================
# Project Solomon Makefile
# ========================

APP_NAME 	:= solomon
BUILD 		?= Debug
GAME 			:= platformer

BIN_DIR 	:= bin
BUILD_DIR := build

CC 				:= gcc
CXX 			:= g++

UNAME_S 	:= $(shell uname -s 2>/dev/null || echo Unknown)
IS_MINGW 	:= $(findstring MINGW,$(UNAME_S))

CSTD 			:= -std=c99
CWARN 		:= -Wall -Wextra -Werror -Wno-unused-parameter
CXXWARN 		:= -Wall -Wextra -Werror -Wno-unused-parameter

ifeq ($(BUILD), Debug)
	COPT := -O0 -g3
else
	COPT := -O2 -DNDEBUG
endif

CFLAGS 	 := $(CSTD) $(CWARN) $(COPT)
CXXFLAGS := $(CXXWARN) $(COPT)

# Uncomment when implementing c imgui
# DEFINES  := -DIMGUI_IMPL_OPENGL_LOADER_GLAD

INCLUDE_DIRS 	:= -I$(wildcard deps/**) -I$(wildcard include/**)

PKG_CFLAGS := $(shell pkg-config --cflags glfw3 2>/dev/null)
PKG_LIBS 	 := $(shell pkg-config --libs glfw3 2>/dev/null)

CFLAGS += $(INCLUDE_DIRS)

ENGINE_CORE := $(wildcard ./engine/*.c) $(wildcard ./engine/**/*.c)
GAME_CORE 	:= $(wildcard ./$(GAME)/*.c) $(wildcard ./$(GAME)/**/*.c)

MAIN_CORE 	:= $(wildcard ./*.c) $(ENGINE_CORE) $(GAME_CORE)

LIBS 				:= $(PKG_LIBS)

OBJECTS 		:= $(patsubst %.c,$(BUILD_DIR)/%.o,$(MAIN_CORE))

ifeq ($(UNAME_S), Linux)
# opengl link flags
	LIBS += -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm
endif

ifeq ($(UNAME_S), Darwin)
	LIBS += -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL
endif

ifneq ($(IS_MINGW),)
	LIBS += -lopengl32 -gdi32
endif

.PHONY: all run clean dirs

all: dirs $(BIN_DIR)/$(APP_NAME)

run: all
	@echo "Running $(APP_NAME) (Game=$(GAME))"
	@./$(BIN_DIR)/$(APP_NAME)

dirs:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(sort $(dir $(OBJECTS)))

$(BIN_DIR)/$(APP_NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
