INC_DIR := includes
OBJ_DIR := obj
SRC_DIR := src

EXE := main

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)


GCC := g++
CPPFLAGS := -I$(INC_DIR) -Wall -MMD -MP -std=c++2a -g

.PHONY: test
test: all
	./$(EXE)

.PHONY: all
all: $(EXE)

$(EXE): $(OBJ)
	$(GCC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(GCC) $(CPPFLAGS) -c $< -o $@

clean:
	rm main
	rm obj/*

