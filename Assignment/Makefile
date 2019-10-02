# Main project executable name.
MAIN_EXEC = tictactoe
# Unit test executable name.
TEST_EXEC = tictactoe_test

# Directory that stores main source code.
MAIN_SRC_DIR = src/main
# Directory that stores unit test code.
TEST_SRC_DIR = src/tests

# Directory that stores main project object files.
MAIN_OBJ_DIR = obj/main
# Directory that stores unit test object files.
TEST_OBJ_DIR = obj/tests

# Main project object files.
MAIN_OBJ = main.o board.o common.o interface.o linked_list.o log.o settings.o
# Unit test object files.
TEST_OBJ = main.o board_test.o common.o linked_list_test.o log_test.o settings_test.o
# Main build object files required for tests.
TEST_REQ_OBJ = board.o linked_list.o log.o settings.o common.o

# C compiler command.
COMPILER = gcc

# Basic C compilation options.
BASE_FLAGS = -ansi -pedantic -Wall -Werror
# C compilation options for main project code.
MAIN_FLAGS = $(BASE_FLAGS)
# C compilation options for test code.
TEST_FLAGS = $(BASE_FLAGS)

# Additional build options.
ifdef SECRET_MODE
MAIN_FLAGS += -D SECRET_MODE
endif
ifdef EDITOR_MODE
MAIN_FLAGS += -D EDITOR_MODE
endif


MAIN_CC = $(COMPILER) $(MAIN_FLAGS)
TEST_CC = $(COMPILER) $(TEST_FLAGS)

# Maps paths to paths inside the main source directory.
MAIN_SRC = $(addprefix $(MAIN_SRC_DIR)/, $(1))
# Maps paths to paths inside the unit test source directory.
TEST_SRC = $(addprefix $(TEST_SRC_DIR)/, $(1))

# Map object files to full paths.
MAIN_OBJ := $(addprefix $(MAIN_OBJ_DIR)/, $(MAIN_OBJ))
TEST_OBJ := $(addprefix $(TEST_OBJ_DIR)/, $(TEST_OBJ))
TEST_REQ_OBJ := $(addprefix $(MAIN_OBJ_DIR)/, $(TEST_REQ_OBJ))


# Main project build rules.

$(MAIN_EXEC) : $(MAIN_OBJ)
	$(MAIN_CC) $^ -o $@

$(MAIN_OBJ_DIR)/main.o : $(call MAIN_SRC, main.c interface.h settings.h)
	$(MAIN_CC) -c $< -o $@

$(MAIN_OBJ_DIR)/board.o : $(call MAIN_SRC, board.c board.h common.h)
	$(MAIN_CC) -c $< -o $@

$(MAIN_OBJ_DIR)/common.o : $(call MAIN_SRC, common.c common.h)
	$(MAIN_CC) -c $< -o $@

$(MAIN_OBJ_DIR)/interface.o : $(call MAIN_SRC, interface.c interface.h board.h common.h log.h settings.h)
	$(MAIN_CC) -c $< -o $@

$(MAIN_OBJ_DIR)/linked_list.o : $(call MAIN_SRC, linked_list.c linked_list.h)
	$(MAIN_CC) -c $< -o $@

$(MAIN_OBJ_DIR)/log.o : $(call MAIN_SRC, log.c log.h common.h linked_list.h)
	$(MAIN_CC) -c $< -o $@

$(MAIN_OBJ_DIR)/settings.o : $(call MAIN_SRC, settings.c settings.h common.h)
	$(MAIN_CC) -c $< -o $@


# Unit test build rules.

$(TEST_EXEC) : $(TEST_OBJ) $(TEST_REQ_OBJ)
	$(TEST_CC) $^ -o $@

$(TEST_OBJ_DIR)/main.o : $(call TEST_SRC, main.c board_test.h linked_list_test.h settings_test.h)
	$(TEST_CC) -c $< -o $@

$(TEST_OBJ_DIR)/common.o : $(call TEST_SRC, common.c common.h)
	$(TEST_CC) -c $< -o $@

$(TEST_OBJ_DIR)/board_test.o : $(call TEST_SRC, board_test.c board_test.h common.h) $(call MAIN_SRC, board.h common.h)
	$(TEST_CC) -c $< -o $@

$(TEST_OBJ_DIR)/linked_list_test.o : $(call TEST_SRC, linked_list_test.c linked_list_test.h common.h) $(call MAIN_SRC, linked_list.h)
	$(TEST_CC) -c $< -o $@

$(TEST_OBJ_DIR)/log_test.o : $(call TEST_SRC, log_test.c log_test.h common.h) $(call MAIN_SRC, log.h common.h)
	$(TEST_CC) -c $< -o $@

$(TEST_OBJ_DIR)/settings_test.o : $(call TEST_SRC, settings_test.c settings_test.h common.h) $(call MAIN_SRC, settings.h)
	$(TEST_CC) -c $< -o $@


# Other build rules.

.PHONY: clean
clean :
	rm -f $(MAIN_EXEC) $(TEST_EXEC) $(MAIN_OBJ) $(TEST_OBJ)
