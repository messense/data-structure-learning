# compiler
CC=clang
# delete file
RM=-rm -f
# make directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=bin
# test source codes directory
TEST_DIR=test

LINKLIST_FILES=iterator.c linklist.c $(TEST_DIR)/test_linklist.c
ADLIST_FILES=adlist.c $(TEST_DIR)/test_adlist.c
STACK_FILES=stack.c $(TEST_DIR)/test_stack.c
QUEUE_FILES=queue.c $(TEST_DIR)/test_queue.c

.PHONY: build
# make build
build: 
# make binary directory first
	$(MKDIR) $(BIN_DIR)
	@echo Starting compile testing codes...
# start compile source codes
	$(CC) helloworld.c -o $(BIN_DIR)/helloworld
	$(CC) $(LINKLIST_FILES) -o $(BIN_DIR)/test_linklist
	$(CC) $(ADLIST_FILES) -o $(BIN_DIR)/test_adlist
	$(CC) $(STACK_FILES) -o $(BIN_DIR)/test_stack
	$(CC) $(QUEUE_FILES) -o $(BIN_DIR)/test_queue

	@echo Finished compiling source codes.
	@echo Go to bin directory to execute them.

.PHONY: clean
# make clean
clean:
	@echo Starting clean built files...
	$(RM) $(BIN_DIR)/*
	@echo Finished cleaning built files 

.PHONY: rebuild
# make rebuild, alias to make clean && make build
rebuild: clean build