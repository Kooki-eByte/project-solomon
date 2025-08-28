# ========================
# Project Solomon Makefile
# ========================

APP_NAME 	:= solomon
BUILD 		?= Debug
GAME 			:= platformer

BIN_DIR 	:= bin
BUILD_DIR := build

IMGUI_DIR 	:= deps/imgui
C_IMGUI_DIR := deps/cimgui

CC 				:= gcc
CXX 			:= g++

UNAME_S 	:= $(shell uname -s 2>/dev/null || echo Unknown)
IS_MINGW 	:= $(findstring MINGW,$(UNAME_S))

CSTD 			:= -std=c99
CXXSTD		:= -std=c++17
CWARN 		:= -Wall -Wextra -Werror -Wno-unused-parameter
CXXWARN 		:= -Wall -Wextra -Werror -Wno-unused-parameter

ifeq ($(BUILD), Debug)
	COPT := -O0 -g
else
	COPT := -O2 -DNDEBUG
endif

CFLAGS 	 := $(CSTD) $(CWARN) $(COPT)
CXXFLAGS := $(CXXSTD) $(CXXWARN) $(COPT)

# Uncomment when implementing c imgui
DEFINES  := -DIMGUI_IMPL_OPENGL_LOADER_GLAD

INCLUDE_DIRS 	:= -Ideps/arena \
	-Ideps/cglm \
	-Ideps/glad \
	-Ideps/KHR \
	-Ideps/stb \
	-Ideps/imgui \
	-Ideps/imgui/backends \
	-Ideps/cimgui

PKG_CFLAGS := $(shell pkg-config --cflags glfw3 sdl3 2>/dev/null)
PKG_LIBS 	 := $(shell pkg-config --libs glfw3 sdl3 2>/dev/null)

CFLAGS 		+= $(DEFINES) $(INCLUDE_DIRS)
CXXFLAGS 	+= $(DEFINES) $(INCLUDE_DIRS)

ENGINE_CORE := $(wildcard ./engine/*.c) \
	$(wildcard ./engine/**/*.c) \
	$(wildcard ./engine/**/**/*.c) \
	$(wildcard ./deps/**/*.c)

GAME_CORE 	:= $(wildcard ./$(GAME)/*.c) $(wildcard ./$(GAME)/**/*.c)

IMGUI_SRC := $(IMGUI_DIR)/imgui.cpp \
	$(IMGUI_DIR)/imgui_draw.cpp \
	$(IMGUI_DIR)/imgui_tables.cpp \
	$(IMGUI_DIR)/imgui_widgets.cpp \
	$(IMGUI_DIR)/backends/imgui_impl_sdl3.cpp \
	$(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp \
	$(C_IMGUI_DIR)/cimgui.cpp \
	$(C_IMGUI_DIR)/imgui_bridge.cpp

MAIN_CORE 	:= $(ENGINE_CORE) $(GAME_CORE)
CXX_SRC 		:= $(IMGUI_SRC)

LIBS 				:= $(PKG_LIBS)

C_OBJECTS 		:= $(patsubst %.c,$(BUILD_DIR)/%.o,$(MAIN_CORE))
CXX_OBJECTS		:= $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(CXX_SRC))
MAIN_OBJ			:= $(C_OBJECTS) $(CXX_OBJECTS)

ifeq ($(UNAME_S), Linux)
# opengl link flags
	LIBS += -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm -lSDL3 -lstdc++
endif

ifeq ($(UNAME_S), Darwin)
	LIBS += -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL
endif

ifneq ($(IS_MINGW),)
	LIBS += -lopengl32 -gdi32
endif

# Linking a bit of C++ (Imgui/Cimgui); link with C== linker for safety
LINKER := $(CXX)

# --- Rules ---
.PHONY: all run clean dirs print

all: dirs $(BIN_DIR)/$(APP_NAME)

run: all
	@echo "Running $(APP_NAME) (Game=$(GAME))"
	@./$(BIN_DIR)/$(APP_NAME)

dirs:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(sort $(dir $(MAIN_OBJ)))

$(BIN_DIR)/$(APP_NAME): $(MAIN_OBJ)
	$(LINKER) $(CXXFLAGS) $^ -o $@ $(LIBS)

# Compile C
$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Cleaning up... One second..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

print:
	@echo "UNAME_S=$(UNAME_S) 	IS_MINGW=$(IS_MINGW)"
	@echo "CFLAGS=$(CFLAGS)"
	@echo "CXXFLAGS=$(CXXFLAGS)"
	@echo "LIBS=$($LIBS)"
	@echo "GAME=$(GAME)"