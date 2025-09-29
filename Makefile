NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -no-pie

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_REPO = https://github.com/42Paris/minilibx-linux.git
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

# Colors for output
GREEN = \033[0;32m
BLUE = \033[0;34m
RED = \033[0;31m
YELLOW = \033[0;33m
NC = \033[0m

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
INCLUDES = -I$(INCLUDE_DIR) -I. -I$(LIBFT_DIR)

# Source files
SRCS = $(SRC_DIR)/cub3d.c \
	$(SRC_DIR)/texture.c \
	${SRC_DIR}/init.c \
	$(SRC_DIR)/map_utils.c \
	$(SRC_DIR)/map_check.c \
	$(SRC_DIR)/clean.c \
	$(SRC_DIR)/utils.c \
	$(SRC_DIR)/events.c \
	$(SRC_DIR)/render.c

# Test source files
TEST_SRCS = $(SRC_DIR)/test_main.c \
	$(SRC_DIR)/render.c \
	$(SRC_DIR)/render_utils.c \
	$(SRC_DIR)/test_render.c

# object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_OBJS = $(TEST_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(MLX_LIB) $(LIBFT_LIB) $(OBJ_DIR) $(NAME)

$(MLX_LIB):
	@if [ ! -d $(MLX_DIR) ]; then \
		echo "Cloning MiniLibX..."; \
		git clone $(MLX_REPO) $(MLX_DIR) --quiet; \
	fi
	@$(MAKE) -s -C $(MLX_DIR)

$(LIBFT_LIB):
	@$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(MLX_FLAGS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) built successfully!$(NC)"

test: $(MLX_LIB) $(LIBFT_LIB) $(OBJ_DIR) $(TEST_OBJS)
	@$(CC) $(CFLAGS) $(TEST_OBJS) $(LIBFT_LIB) $(MLX_FLAGS) -o test_render
	@echo "$(GREEN)✓ test_render built successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling:$(NC) $<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(RED)Cleaning object files..$(NC)"
	@rm -rf $(OBJ_DIR)
	@if [ -d $(MLX_DIR) ]; then $(MAKE) clean -C $(MLX_DIR); fi

fclean: clean
	@echo "$(RED)Removing $(NAME)..$(NC)"
	@rm -f $(NAME) test_render
	@if [ -d $(LIBFT_DIR) ]; then $(MAKE) fclean -C $(LIBFT_DIR); fi
	@echo "$(RED)Removing MLX repository...$(NC)"
	@rm -rf $(MLX_DIR)

rm-mlx:
	@echo "$(RED)Removing MLX repository...$(NC)"
	@rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re rm-mlx test
