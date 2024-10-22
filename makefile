CC				= g++
CPP_FLAGS		= -pedantic -O3 -std=c++17
DEBUG_FLAGS		= -g
LINKER_FLAGS	= -lSDL2 -lSDL2_image -lSDL2_ttf

SRC_DIR			= ./src
BUILD_DIR		= ./build
OUTPUT_DIR		= ./output

GENERAL_SRC		= LTexture.cpp SDLProgram.cpp Button.cpp
BUTTON_SRC		= ButtonDemo.cpp
RENDER_DEMO_SRC = SDLRenderDemo.cpp
ANIM_DEMO_SRC	= SDLAnimationDemo.cpp
MAIN_SRC		= main.cpp

GENERAL_OBJ		= $(addprefix $(BUILD_DIR)/,$(GENERAL_SRC:.cpp=.o))
BUTTON_OBJ		= $(addprefix $(BUILD_DIR)/,$(BUTTON_SRC:.cpp=.o))
RENDER_DEMO_OBJ	= $(addprefix $(BUILD_DIR)/,$(RENDER_DEMO_SRC:.cpp=.o))
ANIM_DEMO_OBJ	= $(addprefix $(BUILD_DIR)/,$(ANIM_DEMO_SRC:.cpp=.o))

OUTPUT_BIN		= game.out
DEBUG_BIN		= debug.out

# Create output directory
$(shell mkdir -p $(BUILD_DIR) $(OUTPUT_DIR))

all: $(SRC_DIR)/$(MAIN_SRC) $(GENERAL_OBJ) button animation render
	$(CC) $(CPP_FLAGS) $< $(BUILD_DIR)/*.o -o $(OUTPUT_DIR)/$(OUTPUT_BIN) $(LINKER_FLAGS)

debug: $(SRC_DIR)/$(MAIN_SRC) $(GENERAL_OBJ) button animation render
	$(CC) $(CPP_FLAGS) $(DEBUG_FLAGS) $< $(BUILD_DIR)/*.o -o $(OUTPUT_DIR)/$(DEBUG_BIN) $(LINKER_FLAGS)

button: $(BUTTON_OBJ)

render: $(RENDER_DEMO_OBJ)

animation: $(ANIM_DEMO_OBJ)


$(BUTTON_OBJ): $(SRC_DIR)/$(BUTTON_SRC)
	$(CC) $(CPP_FLAGS) -c $< -o $(BUTTON_OBJ)

$(RENDER_DEMO_OBJ): $(SRC_DIR)/$(RENDER_DEMO_SRC)
	$(CC) $(CPP_FLAGS) -c $< -o $(RENDER_DEMO_OBJ)

$(ANIM_DEMO_OBJ): $(SRC_DIR)/$(ANIM_DEMO_SRC)
	$(CC) $(CPP_FLAGS) -c $< -o $(ANIM_DEMO_OBJ)

$(BUILD_DIR)/LTexture.o: $(SRC_DIR)/LTexture.cpp
	$(CC) $(CPP_FLAGS) -c $< -o $@

$(BUILD_DIR)/SDLProgram.o: $(SRC_DIR)/SDLProgram.cpp
	$(CC) $(CPP_FLAGS) -c $< -o $@

$(BUILD_DIR)/Button.o: $(SRC_DIR)/Button.cpp
	$(CC) $(CPP_FLAGS) -c $< -o $@


clean:
	rm -rf $(BUILD_DIR) $(OUTPUT_DIR)
