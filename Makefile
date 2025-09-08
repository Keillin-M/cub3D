NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = Libft
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

# Verbose mode control
ifdef VERBOSE
    QUIET =
else
    QUIET = @
endif

# Directories
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
INCLUDES = -I$(INCLUDE_DIR) -I. -I$(LIBFT_DIR)

# Source files
SRCS = $(SRC_DIR)/cub3D.c \
	$(SRC_DIR)/utils.c \

# object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(MLX_LIB) $(LIBFT_LIB) $(OBJ_DIR) $(NAME)

$(MLX_LIB):
	@if [ ! -d $(MLX_DIR) ]; then \
		echo "Cloning MiniLibX..."; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	$(QUIET)$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	$(QUIET)$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(QUIET)$(CC) $(CFLAGS) $(MLX_FLAGS) $(LIBFT_LIB) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) built successfully!$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling:$(NC) $<"
	$(QUIET)$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	$(QUIET)mkdir -p $(OBJ_DIR)

clean:
	@echo "$(RED)Cleaning object files..$(NC)"
	$(QUIET)rm -rf $(OBJ_DIR)
	@if [ -d $(MLX_DIR) ]; then $(MAKE) clean -C $(MLX_DIR); fi

fclean: clean
	@echo "$(RED)Removing $(NAME)..$(NC)"
	$(QUIET)rm -f $(NAME)
	@if [ -d $(LIBFT_DIR) ]; then $(MAKE) fclean -C $(LIBFT_DIR); fi

rm-mlx:
	@echo "$(RED)Removing MLX repository...$(NC)"
	$(QUIET)rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re rm-mlx
