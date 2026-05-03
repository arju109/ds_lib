# =========================================================
# Makefile — Data Structures Library
# Usage:
#   make          Build the static library
#   make test     Build & run all unit tests
#   make clean    Remove build artifacts
#   make valgrind Run tests under valgrind (memory check)
#   make docs     Generate Doxygen HTML docs
# =========================================================

CC      = gcc
CFLAGS  = -Wall -Wextra -Wpedantic -std=c11 -g
IFLAGS  = -Iinclude
AR      = ar
ARFLAGS = rcs

# Directories
SRC_DIR   = src
INC_DIR   = include
TEST_DIR  = tests
BUILD_DIR = build
LIB_DIR   = lib

# Source and object files
SRCS    = $(wildcard $(SRC_DIR)/*.c)
OBJS    = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Test sources (all .c in tests/, except framework header)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/test_%.o, $(TEST_SRCS))

# Output targets
LIB_NAME = libds.a
LIB_OUT  = $(LIB_DIR)/$(LIB_NAME)
TEST_BIN = $(BUILD_DIR)/run_tests

# ---- Default target: build library -------------------------

.PHONY: all
all: dirs $(LIB_OUT)
	@echo ""
	@echo "  Library built: $(LIB_OUT)"
	@echo "  Run 'make test' to execute the test suite."
	@echo ""

# ---- Create build directories ------------------------------

.PHONY: dirs
dirs:
	@mkdir -p $(BUILD_DIR) $(LIB_DIR)

# ---- Compile source files ----------------------------------

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

# ---- Build static library ----------------------------------

$(LIB_OUT): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# ---- Compile test files ------------------------------------

$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.c
	$(CC) $(CFLAGS) $(IFLAGS) -I$(TEST_DIR) -c $< -o $@

# ---- Link and run tests ------------------------------------

.PHONY: test
test: dirs $(LIB_OUT) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) -L$(LIB_DIR) -lds -o $(TEST_BIN)
	@echo ""
	@./$(TEST_BIN)

# ---- Valgrind memory check ---------------------------------

.PHONY: valgrind
valgrind: test
	@echo "\n--- Running valgrind memory check ---\n"
	valgrind --leak-check=full --error-exitcode=1 $(TEST_BIN)

# ---- Doxygen docs ------------------------------------------

.PHONY: docs
docs:
	@command -v doxygen >/dev/null 2>&1 \
		&& doxygen docs/Doxyfile \
		|| echo "  doxygen not installed — skipping docs."

# ---- Clean -------------------------------------------------

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(LIB_DIR)
	@echo "  Cleaned."
