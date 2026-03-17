#
# EPITECH PROJECT, 2026
# cuddle
# File description:
# Main building makefile
# Auto-Generated with Episetup by Amélie
# Author:
# Amélie Ambleton--Guth
#



NAME = libcuddle.a


# --- Paths ---
SRC_DIR		=	src
OBJ_DIR		=	build
INC_DIR		=	include


# --- Files ---
SRC		=	\
			cuddle.c \
			explode.c \
			mem_utils.c \
			cuddle_logging.c \
			cuddle_write.c \
			cuddle_display.c \
			transformation.c \
            str_to_nb.c
OBJ		=	$(SRC:%.c=$(OBJ_DIR)/%.o)
DEPS	=	$(OBJ:.o=.d)


# --- Compilation Flags ---
CC			?=	epiclang
CFLAGS		=	-pedantic -I$(INC_DIR) -g


# --- Make Targets ---
all: $(NAME) libtest
$(NAME): $(OBJ)
	@printf "\033[32m[LD]\033[0m %s\n" $@
	@ar rc $(NAME) $(OBJ)
	@printf "\033[1;32m[Build Success]\033[0m %s\nCompiler: %s\nC Flags: %s\n---\n" "$@" "ar" "$(CFLAGS)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@printf "\033[32m[CC]\033[0m %s\n" $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR) $(BIN_DIR):
	@mkdir -p $@

libtest: $(NAME)
	clang $(CFLAGS) -o libtest src/main.c -L. -lcuddle -lm

clean:
	@rm -rf $(OBJ_DIR)
	@rm -f $(DEPS)

fclean: clean
	@rm -rf $(NAME) libtest

re: fclean all

.PHONY: all clean fclean re debug libtest
