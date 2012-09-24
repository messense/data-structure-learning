# compiler
CC=clang
# delete file
RM=-rm -f
# make directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin

# source codes directory
SRC_DIR=../src

LINKLIST_FILES=$(SRC_DIR)/iterator.c $(SRC_DIR)/linklist.c test_linklist.c
ADLIST_FILES=$(SRC_DIR)/adlist.c test_adlist.c
STACK_FILES=$(SRC_DIR)/stack.c test_stack.c
QUEUE_FILES=$(SRC_DIR)/queue.c test_queue.c

.PHONY: build
# make build
build: 
# make binary directory first
	$(MKDIR) $(BIN_DIR)
	@echo Starting compile testing codes...
# start compile source codes
	$(CC) $(LINKLIST_FILES) -o $(BIN_DIR)/test_linklist
	$(CC) $(ADLIST_FILES) -o $(BIN_DIR)/test_adlist
	$(CC) $(STACK_FILES) -o $(BIN_DIR)/test_stack
	$(CC) $(QUEUE_FILES) -o $(BIN_DIR)/test_queue

	@echo Finished compiling source codes.
	@echo Go to bin directory to execute them.

.PHONY: clean
# make clean
clean:
	@echo Starting clean built test binary files...
	$(RM) $(BIN_DIR)/test_*
	@echo Finished cleaning built test binary files 