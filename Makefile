SRC_DIR=FastDynamic
OBJ_DIR=obj

CC=g++
CFLAGS=-std=c++17 -g -O2
EXECUTABLE := gfinder
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

$(EXECUTABLE): $(OBJ)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -w -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(OBJ_DIR) $(EXECUTABLE)

test:
	./$(EXECUTABLE) test_dataset/data1.format test_dataset/query3.format test_dataset/predicate_similarity.txt 1 30 10 10 0

