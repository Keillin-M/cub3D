NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -no-pie

# Libraries
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(INCLUDE_DIR) -I. -I$(LIBFT_DIR)

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
CUB3D_DIR = $(SRC_DIR)/cub3d
MINIMAP_DIR = $(SRC_DIR)/minimap
PARSER_DIR = $(SRC_DIR)/parser
RENDER_DIR = $(SRC_DIR)/render
UTILS_DIR = $(SRC_DIR)/utils

# Source files
CUB3D_SRCS = $(CUB3D_DIR)/cub3d.c \
	$(CUB3D_DIR)/events.c \
	$(CUB3D_DIR)/move_rotate.c \
	$(CUB3D_DIR)/welcome_banner.c
PARSER_SRCS = $(PARSER_DIR)/init.c \
	$(PARSER_DIR)/color_check.c \
	$(PARSER_DIR)/map_check.c \
	$(PARSER_DIR)/map_utils.c \
	$(PARSER_DIR)/read.c \
	$(PARSER_DIR)/texture_check.c
MINIMAP_SRCS = $(MINIMAP_DIR)/minimap.c \
	$(MINIMAP_DIR)/minimap_draw.c
RENDER_SRCS = $(RENDER_DIR)/draw.c \
	$(RENDER_DIR)/draw_utils.c \
	$(RENDER_DIR)/render.c \
	$(RENDER_DIR)/render_utils.c \
	$(RENDER_DIR)/init_ray.c \
	$(RENDER_DIR)/raycast.c \
	$(RENDER_DIR)/texture_load.c \
	$(RENDER_DIR)/texture_utils.c
UTILS_SRCS = $(UTILS_DIR)/clean.c \
	$(UTILS_DIR)/utils.c

SRCS = $(CUB3D_SRCS) $(PARSER_SRCS) $(MINIMAP_SRCS) \
	$(RENDER_SRCS) $(UTILS_SRCS)

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

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



$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling:$(NC) $<"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(RED)Cleaning object files..$(NC)"
	@rm -rf $(OBJ_DIR)
	@if [ -d $(LIBFT_DIR) ]; then $(MAKE) clean -C $(LIBFT_DIR); fi
	@if [ -d $(MLX_DIR) ]; then $(MAKE) clean -C $(MLX_DIR); fi

fclean: clean
	@echo "$(RED)Removing $(NAME)..$(NC)"
	@rm -f $(NAME)
	@if [ -d $(LIBFT_DIR) ]; then $(MAKE) fclean -C $(LIBFT_DIR); fi
	@echo "$(RED)Removing MLX repository...$(NC)"
	@rm -rf $(MLX_DIR)

rm-mlx:
	@echo "$(RED)Removing MLX repository...$(NC)"
	@rm -rf $(MLX_DIR)

re: fclean all

.PHONY: all clean fclean re rm-mlx
