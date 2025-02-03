BIN_DIR := bin
INC_DIR := include
LIB_DIR := lib
SRC_DIR := src
OBJ_DIR := obj

EXE := $(BIN_DIR)/burgers
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

CXX := g++
CPPFLAGS := -I$(INC_DIR) -MMD -MP -g
CFLAGS := -Wall
LDFLAGS := -L$(LIB_DIR)
LDLIBS := -lm

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rfv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)