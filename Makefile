
# Program name
NAME = cub3D

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Source and Objects files
SRC = $(wildcard src/*.c src/*/*.c)
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
RM = rm -f

MLX42_DIR = MLX42
MLX42_BUILD = $(MLX42_DIR)/build
MLX42_LIB = $(MLX42_BUILD)/libmlx42.a
MLX42_INC = -I$(MLX42_DIR)/include
MLX42_FLAGS = -ldl -lglfw -pthread -lm

INC = -Iinclude

# Rules
all: $(MLX42_LIB) $(NAME)

$(MLX42_LIB):
	cmake -B $(MLX42_BUILD) $(MLX42_DIR)
	cmake --build $(MLX42_BUILD) -j4

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX42_LIB) $(MLX42_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) $(MLX42_INC) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

