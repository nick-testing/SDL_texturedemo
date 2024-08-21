CC= g++
CPP_FLAGS= -pedantic
DEBUG_FLAGS= -g
LINKER_FLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf
SRC_DIR= ./src/
OBJ_NAME= $(SRC_DIR)main.o $(SRC_DIR)SDLRenderDemo.o $(SRC_DIR)LTexture.o $(SRC_DIR)SDLProgram.o $(SRC_DIR)SDLAnimationDemo.o
OUTPUT= output
OUTPUT_BIN= game.out
DEBUG_BIN= debug.out

# Create output directory
$(shell mkdir -p $(OUTPUT))

all: $(OUTPUT_BIN)

$(OUTPUT_BIN): $(OBJ_NAME)
	$(CC) $(OBJ_NAME) -o $(OUTPUT)/$(OUTPUT_BIN) $(LINKER_FLAGS)

%.o: $(SRC_DIR)%.cpp
	$(CC) $<  $(CPP_FLAGS) -o $(OBJ_NAME)

debug: $(DEBUG_BIN)

$(DEBUG_BIN):
	$(CC) $(SRC_DIR)*.cpp $(DEBUG_FLAGS) -o $(OUTPUT)/$(DEBUG_BIN) $(LINKER_FLAGS)

clean:
	rm -rf $(OUTPUT) $(SRC_DIR)*.o