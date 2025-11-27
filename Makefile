NAME := libnori.a

CC := gcc
CFLAGS := -std=c99 -Wall -Wpedantic -Wc90-c99-compat
CPPFLAGS = -MMD -MP -I $(INCLUDE_DIR)
LDFLAGS = -lm -lbstr -L $(LIBRARY_DIR)
AR := ar
ARFLAGS := -r -c -s 

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

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

-include $(DEP)

clean:
	rm -f $(OBJ) $(DEP)

fclean: clean
	rm -f $(NAME)

debug: CFLAGS += -g3 $(SANFLAGS)
debug: LDFLAGS += $(SANFLAGS)
debug: $(NAME)

release: CFLAGS += -O2 -DNDEBUG
release: fclean $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean fclean re
.SILENT:
