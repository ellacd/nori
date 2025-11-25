EXE := NoriTest

CC := gcc
CFLAGS := -std=c99 -Wall -Wpedantic
CPPFLAGS = -MMD -MP -I $(INCLUDE_DIR)
LDFLAGS = -lm -lbstr -L $(LIBRARY_DIR)

SANFLAGS := -fsanitize=address,undefined
MAKEFLAGS := --no-print-directory

SRC_DIR := src
BUILD_DIR := .build
INCLUDE_DIR := include
LIBRARY_DIR := lib

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

all: debug

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(EXE)

debug: CFLAGS += -g3 $(SANFLAGS)
debug: LDFLAGS += $(SANFLAGS)
debug: $(EXE)

release: CFLAGS += -O3 -DNDEBUG
release: fclean $(EXE)

test: $(EXE)
	gdb --tui $<

.PHONY: clean fclean test
.SILENT:
