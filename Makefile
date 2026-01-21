NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = src/main.c
OBJ = $(SRC:.c=.o)

MLX42_DIR = MLX42
MLX42_BUILD = $(MLX42_DIR)/build
MLX42_LIB = $(MLX42_BUILD)/libmlx42.a
MLX42_INC = -I$(MLX42_DIR)/include
MLX42_FLAGS = -ldl -lglfw -pthread -lm

INC = -Iinclude

all: $(MLX42_LIB) $(NAME)

$(MLX42_LIB):
	cmake -B $(MLX42_BUILD) $(MLX42_DIR)
	cmake --build $(MLX42_BUILD) -j4

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX42_LIB) $(MLX42_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) $(MLX42_INC) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

