# Makefile variables
## compiler command
CC=gcc
## compiler flags
CC_FLAGS=-I$(INCLUDE_DIR) 
## compiler sanitizer options
SANITIZE_FLAGS=-g -fsanitize=undefined -fsanitize=bounds -fno-omit-frame-pointer -g
## -fsanitize=address
## directory for source files
SRC_DIR=src
## directory for header files
INCLUDE_DIR=include
## directory for object files (.o)
BUILD_DIR=build
## directory for executables files
BIN_DIR=bin
## directory for Doxygen documentation
DOCS_DIR=docs

# Targets that don't actually create files
.PHONY: all clean test docs

# Default target
all: directories $(BIN_DIR)/simple_bst $(BIN_DIR)/avl_bst $(BIN_DIR)/rb_bst $(BIN_DIR)/heap $(BIN_DIR)/priority_queue

# Create working directories if needed ?
directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

# Generate Doxygen documentation
docs: 
	@rm -rf $(DOCS_DIR)
	@mkdir -p $(DOCS_DIR)
	doxygen Doxyfile

# main bst object file
$(BUILD_DIR)/main_bst.o: $(SRC_DIR)/main_bst.c $(INCLUDE_DIR)/bst.h
	$(CC) $(CC_FLAGS) $(SANITIZE_FLAGS) -c -o $@ $<

# simple_btree binary file
$(BIN_DIR)/simple_bst: $(BUILD_DIR)/main_bst.o $(BUILD_DIR)/simple_bst.o
	$(CC) $(CC_FLAGS) $(SANITIZE_FLAGS) -o $@ $^

# simple_btree object file 
$(BUILD_DIR)/simple_bst.o: $(SRC_DIR)/simple_bst.c $(INCLUDE_DIR)/bst.h
	$(CC) $(CC_FLAGS) $(SANITIZE_FLAGS) -c -o $@ $<

# avl_btree binary file 
$(BIN_DIR)/avl_bst: $(BUILD_DIR)/main_bst.o $(BUILD_DIR)/avl_bst.o
	$(CC) $(CC_FLAGS) $(SANITIZE_FLAGS) -o $@ $^

# avl_btree object file
$(BUILD_DIR)/avl_bst.o: $(SRC_DIR)/avl_bst.c $(INCLUDE_DIR)/bst.h
	$(CC) $(CC_FLAGS) $(SANITIZE_FLAGS) -c -o $@ $<

# rb_btree binary file
$(BIN_DIR)/rb_bst: $(BUILD_DIR)/main_bst.o $(BUILD_DIR)/rb_bst.o
	$(CC) $(CC_FLAGS) $(SANITIZE_FLAGS) -o $@ $^

# rb_btree object file 
$(BUILD_DIR)/rb_bst.o: $(SRC_DIR)/rb_bst.c $(INCLUDE_DIR)/bst.h
	$(CC) $(CC_FLAGS) $(SANITIZE_FLAGS) -c -o $@ $<

# heap binary file
$(BIN_DIR)/heap: $(BUILD_DIR)/heap.o $(BUILD_DIR)/main_heap.o
	$(CC) $(CC_FLAGS) $(SANITIZE_FLAGS) -o $@ $^

# heap object file
$(BUILD_DIR)/heap.o: $(SRC_DIR)/heap.c $(INCLUDE_DIR)/heap.h
	$(CC) $(CC_FLAGS) $(SANITIZE_FLAGS) -c -o $@ $<

# main_heap object file
$(BUILD_DIR)/main_heap.o: $(SRC_DIR)/main_heap.c $(INCLUDE_DIR)/heap.h
	$(CC) $(CC_FLAGS) $(SANITIZE_FLAGS) -c -o $@ $<

# heapsort binary file
#$(BIN_DIR)/heapsort: $(BUILD_DIR)/heapsort.o $(BUILD_DIR)/main_heapsort.o
#	$(CC) $(CC_FLAGS) $(SANITIZE_FLAGS) -o $@ $^

# heapsort object file
#$(BUILD_DIR)/heapsort.o: $(SRC_DIR)/heap.c $(INCLUDE_DIR)/heap.h
#	$(CC) $(CC_FLAGS) $(SANITIZE_FLAGS) -c -o $@ $<

# main_heapsort object file
#$(BUILD_DIR)/main_heapsort.o: $(SRC_DIR)/main_heapsort.c $(INCLUDE_DIR)/heap.h
#	$(CC) $(CC_FLAGS) $(SANITIZE_FLAGS) -c -o $@ $<

# priority queue binary file
$(BIN_DIR)/priority_queue: $(BUILD_DIR)/priority_queue.o $(BUILD_DIR)/main_priority_queue.o $(BUILD_DIR)/simple_bst.o
	$(CC) $(CC_FLAGS) $(SANITIZE_FLAGS) -o $@ $^

# priority queue object file
$(BUILD_DIR)/priority_queue.o: $(SRC_DIR)/priority_queue.c $(INCLUDE_DIR)/queue.h $(INCLUDE_DIR)/bst.h
	$(CC) $(CC_FLAGS) $(SANITIZE_FLAGS) -c -o $@ $<

# main_priority_queue object file
$(BUILD_DIR)/main_priority_queue.o: $(SRC_DIR)/main_priority_queue.c $(INCLUDE_DIR)/queue.h
	$(CC) $(CC_FLAGS) $(SANITIZE_FLAGS) -c -o $@ $<

# Test execution
test: all
	@echo "--== TEST - simple (unbalanced) bst via $(BIN_DIR)/simple_bst ==--"
	./bin/simple_bst -v 20 -10 30 40 p f 30 f 60 60 25 50 p r -10 p r 40 p
	@echo ""
	@echo ""
	@echo ""
	@echo "--== TEST - avl (balanced) bst via $(BIN_DIR)/avl_bst ==--"
	./bin/avl_bst -v 20 -10 30 40 p f 30 f 60 60 25 50 p r -10 p r 40 p
	@echo ""
	@echo ""
	@echo ""
	@echo "--== TEST - red-black (balanced) bst via $(BIN_DIR)/rb_bst ==--"
	./bin/rb_bst -v 20 -10 30 40 p f 30 f 60 60 25 50 p r -10 p r 40 p


# Clean up
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(DOCS_DIR) *~ $(SRC_DIR)/*~ $(INCLUDE_DIR)/*~

