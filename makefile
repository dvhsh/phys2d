CC = gcc-14
CFLAGS = -g -I./include -I../libGenesis/include -I../libEntropy/include -I/opt/homebrew/include
LDFLAGS = -L../libGenesis/build -L../libEntropy/build -L/opt/homebrew/lib \
          -lgenesis -lentropy -lsimple2d -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf \
          -framework OpenGL

BUILD_DIR = dist
SRC_DIR = src
INCLUDE_DIR = include
RESOURCES_DIR = resources

# Find all .c files recursively in src directory
SOURCES = $(shell find $(SRC_DIR) -name '*.c')
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
TARGET = $(BUILD_DIR)/main

all: $(TARGET) copy_resources

$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Copy resources to build directory
copy_resources:
	@mkdir -p $(BUILD_DIR)/resources/fonts
	cp $(RESOURCES_DIR)/fonts/JetBrainsMono-Regular.ttf $(BUILD_DIR)/resources/fonts/

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean copy_resources