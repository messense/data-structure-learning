BIN_DIR=bin
TEST_DIR=test

LINKLIST_FILES=linklist.c $(TEST_DIR)/test_linklist.c
ADLIST_FILES=adlist.c $(TEST_DIR)/test_adlist.c

build: 
	clang $(LINKLIST_FILES) -o $(BIN_DIR)/test_linklist
	clang $(ADLIST_FILES) -o $(BIN_DIR)/test_adlist

clean:
	-rm $(BIN_DIR)/*