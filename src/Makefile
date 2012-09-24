# compiler
CC=clang
# delete file
RM=-rm -f
# make directory
MKDIR=-mkdir -p
# binary file directory
BIN_DIR=../bin

.PHONY: build
# make build
build: 
# make binary directory first
	$(MKDIR) $(BIN_DIR)
	@echo Starting compile algorithm codes...
# start compile source codes
	$(CC) helloworld.c -o $(BIN_DIR)/helloworld

	@echo Finished compiling source codes.
	@echo Go to bin directory to execute them.

.PHONY: clean
# make clean
clean:
	@echo Starting clean built algorithm binary files...
	$(RM) $(BIN_DIR)/al_*
	@echo Finished cleaning built algorithm binary files 