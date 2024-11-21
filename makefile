CC = gcc-14
CFLAGS = -g -I./include \
           -I../libGenesis/include \
           -I../libEntropy/include \
           -I../libAxiom/include \
           -I/opt/homebrew/include

LDFLAGS = -L../libGenesis/build \
          -L../libEntropy/build \
          -L../libAxiom/build \
          -L/opt/homebrew/lib \
          -lgenesis -lentropy -laxiom \
          -lsimple2d -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf \
          -framework OpenGL

BUILD_DIR = dist
SRC_DIR = src
INCLUDE_DIR = include

# Find all .c files recursively in src directory
SOURCES = $(shell find $(SRC_DIR) -name '*.c')
# Generate object file names
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
# Final executable
TARGET = $(BUILD_DIR)/main

all: $(TARGET)

# Link object files into executable
$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
