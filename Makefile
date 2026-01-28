
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

# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

MLX42_DIR = MLX42
MLX42_BUILD = $(MLX42_DIR)/build
MLX42_LIB = $(MLX42_BUILD)/libmlx42.a
MLX42_INC = -I$(MLX42_DIR)/include
MLX42_FLAGS = -ldl -lglfw -pthread -lm

INC = -Iinclude $(LIBFT_INC) $(MLX42_INC)

# Rules
all: $(LIBFT) $(MLX42_LIB) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLX42_LIB):
	cmake -B $(MLX42_BUILD) $(MLX42_DIR)
	cmake --build $(MLX42_BUILD) -j4

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX42_LIB) $(MLX42_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

