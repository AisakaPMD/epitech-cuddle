#
# EPITECH PROJECT, 2026
# Benjalib
# File description:
# Main building makefile
# Auto-Generated with Episetup by Amélie
# Author:
# Amélie Ambleton--Guth
# Feb 2026
#

NAME = libbenja.a

SRC_FILENAMES := \
	printf/my_printf.c \
	printf/printf_utils.c \
	printf/printf_utils_strbuf.c \
	printf/printf_utils_str.c \
	printf/printf_utils_misc.c \
	printf/printf_utils_float.c \
	printf/printf_utils_nbr.c \
	printf/printf_specifier_g.c \
	printf/printf_specifier_x.c \
	printf/printf_specifier_e.c \
	printf/printf_specifier_a.c \
	printf/printf_specifier_b.c \
	printf/printf_specifier_c.c \
	printf/printf_specifier_u.c \
	printf/printf_specifier_s.c \
	printf/printf_specifier_o.c \
	printf/printf_specifier_p.c \
	printf/printf_specifier_n.c \
	printf/printf_specifier_m.c \
	printf/printf_specifier_di.c \
	printf/printf_specifier_f.c \
	printf/printf_main_dprintf.c \
	printf/printf_main_vdprintf.c \
	printf/printf_main_fprintf.c \
	printf/printf_main_vfprintf.c \
	printf/printf_main_sprintf.c \
	printf/printf_main_vsprintf.c \
	printf/printf_main_snprintf.c \
	printf/printf_main_vsnprintf.c \
	printf/printf_main_printf.c \
	printf/printf_main_vprintf.c \
	\
	my/math_utils.c \
	my/nbr_utils.c \
	my/pointer_utils.c \
	my/str_utils.c \
	my/str_utils_2.c \
	my/str_utils_3.c \
	my/str_utils_4.c \
	my/misc_utils.c \
	my/str_checks.c \
	my/chr_checks.c \
	my/explode.c \
	my/mem_utils.c \
	\
	linkedlist/ll_adders.c \
	linkedlist/ll_removers.c \
	linkedlist/ll_utils.c \
	\
	arraylist/al_adders.c \
	arraylist/al_removers.c \
	arraylist/al_utils.c \
	\
	hashtable/ht_adding.c \
	hashtable/ht_printing.c \
	hashtable/ht_fetching.c \
	hashtable/ht_removing.c \
	hashtable/ht_main.c \
	hashtable/ht_utils.c

HEADERS = \
	benjalib/linked_list.h \
	benjalib/array_list.h \
	benjalib/my.h \
	benjalib/my_printf.h \
	benjalib/system_includes.h \
	benjalib/hashtable.h \
	benjalib.h


SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin
HEADERS_DIR = include

SRC_FILES = $(SRC_FILENAMES:%=$(SRC_DIR)/%)
OBJ_FILES = $(SRC_FILENAMES:%.c=$(OBJ_DIR)/%.o)
HEADER_FILES = $(HEADERS:%=$(HEADERS_DIR)/%)

libtest: CFLAGS += -g
codingstyle: CC = epiclang

export CC
export CFLAGS

all: $(NAME)

$(NAME): $(OBJ_FILES) | $(BIN_DIR)
	ar rc $(NAME) $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER_FILES) | $(OBJ_DIR)
	mkdir -p $(dir $@) && $(CC) -I$(HEADERS_DIR) $(CFLAGS) -c $< -o $@ $(EXTRA_FLAGS)

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR) *.gcda *.gcno *.gcov *.gcov.json.gz *.profraw

fclean: clean
	rm -rf $(BIN_DIR)
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

codingstyle: $(NAME)

.PHONY: re fclean clean all codingstyle 
