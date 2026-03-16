#
# EPITECH PROJECT, 2026
# bscuddle
# File description:
# Main building makefile
# Auto-Generated with Episetup by Amélie
# Author:
# Amélie Ambleton--Guth
#

NAME = bscuddle
SRC_FILENAMES = main.c	\
				transformation.c	\
				str_to_nb.c
HEADERS = benjalib.h


SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin
LIBS_DIR = lib
HEADERS_DIR = include

SRC_FILES = $(SRC_FILENAMES:%=$(SRC_DIR)/%)
OBJ_FILES = $(SRC_FILENAMES:%.c=$(OBJ_DIR)/%.o)
BIN_FILE = $(BIN_DIR)/$(NAME)
HEADER_FILES = $(HEADERS:%=$(HEADERS_DIR)/%)

LIBMY_DIR = $(LIBS_DIR)/benjalib
LIBMY_MAKE = $(MAKE) -C $(LIBMY_DIR)
LIBMY_BIN = libbenja.a

CFLAGS += -g -I$(HEADERS_DIR)
LINKER_FLAGS += -Llib/benjalib -lbenja

codingstyle: CC = epiclang

# Extra flags reserved for gcovr profiling flags

export CC

all: $(NAME)
	
$(NAME): $(BIN_FILE)
	ln -sf $(BIN_FILE) $(NAME)

$(BIN_FILE): $(OBJ_FILES) $(LIBS_DIR)/$(LIBMY_BIN) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_FILE) $(OBJ_FILES) $(LINKER_DIRS) $(LINKER_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER_FILES) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(EXTRA_FLAGS)

$(LIBS_DIR)/$(LIBMY_BIN):
	$(LIBMY_MAKE) all
	cp $(LIBMY_DIR)/$(LIBMY_BIN) $(LIBS_DIR)/

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) *.gcda *.gcno *.gcov *.gcov.json.gz *.profraw
	$(LIBMY_MAKE) clean 

fclean: clean
	rm -rf $(BIN_DIR)
	$(LIBMY_MAKE) fclean
	rm -f $(LIBS_DIR)/$(LIBMY_BIN)

re:
	$(MAKE) fclean
	$(MAKE) all

run: $(BIN_FILE)
	./$(BIN_FILE)

codingstyle:
	$(MAKE) clean
	rm -rf $(BIN_DIR)
	$(MAKE) all

.PHONY: re fclean clean all codingstyle run
