.PHONY: all clean bonus fclean re

NAME = cub3D

LIBFT_DIR = ./libs/libft

LIBFT = $(LIBFT_DIR)libft.a

LIBMLX_DIR = ./libs/mlx

LIBMLX = $(LIBMLX_DIR)libmlx.dylib

MAKE = make

CLEAN = clean

FCLEAN = fclean

SRC = sprite.c get_sprite.c struct_cub.c utils.c parser.c ./gnl/get_next_line.c

OBJ = $(SRC:.c=.o)

CC = gcc

FLAG = -Wall -Werror -Wextra -g -O

FLAGMLX = -framework OpenGL -framework AppKit

OPTION = -c -D GL_SILENCE_DEPRECATION

OPTIONOBJ = -o

DEL = rm -rf

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX)
	@cd $(LIBFT_DIR) && mv ./libft.a ../../
	@cd $(LIBMLX_DIR) && mv ./libmlx.dylib ../../
	@$(CC) $(FLAG) $(OBJ) -L. -lmlx -L. -lft $(FLAGSMLX) $(OPTIONOBJ) $(NAME)

$(LIBFT):
	@cd $(LIBFT_DIR) && $(MAKE)

$(LIBMLX):
	@cd $(LIBMLX_DIR) && $(MAKE)

clean:
	@$(DEL) $(OBJ)
	@cd $(LIBFT_DIR) && $(MAKE) $(CLEAN)
	@cd $(LIBMLX_DIR) && $(MAKE) $(CLEAN)

fclean: clean
	@$(DEL) $(NAME) ./libmlx.dylib
	@$(DEL) $(OBJ)
	@cd $(LIBFT_DIR) && $(MAKE) $(FCLEAN)

re: fclean all
