BIN_DIR := bin
INC_DIR := include
LIB_DIR := lib
OBJ_DIR := obj
RES_DIR := results
SRC_DIR := src

EXE := $(BIN_DIR)/burgers
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

CXX := g++
CPPFLAGS := -I$(INC_DIR) -MMD -MP -fopenmp -g
CFLAGS := -Wall
LDFLAGS := -L$(LIB_DIR) -fopenmp
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
	rm -rfv $(BIN_DIR) $(OBJ_DIR) $(RES_DIR)/*.txt

-include $(OBJ:.o=.d)