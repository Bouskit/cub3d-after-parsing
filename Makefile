NAME = cub3d

SRCS = srcs/main.c \
       srcs/main_2.c \
	   srcs/mouse_b.c \
       srcs/utils_mlx.c \
       srcs/utils_mlx_2.c \
       srcs/utils_mlx_3.c \
       srcs/raycasting.c \
       srcs/raycasting_2.c \
       srcs/draw.c \
       srcs/texture.c \
       srcs/dda.c \
       srcs/dda_2.c \
       srcs/utils.c \
       srcs/parsing/parsing_color.c \
       srcs/parsing/parsing_map.c \
       srcs/parsing/parsing_map2.c \
       srcs/parsing/parsing_texture.c \
       srcs/parsing/parsing_utils.c \
       srcs/parsing/parsing.c \
       srcs/minimap.c \

OBJ_DIR = obj
OBJS = $(SRCS:.c=.o)
OBJS := $(patsubst srcs/%, $(OBJ_DIR)/%, $(OBJS))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ./lib/libft_custom
MLX_DIR = ./lib/minilibx

LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

GREEN = \033[0;32m
RESET = \033[0m

$(NAME): $(MLX_LIB) $(LIBFT) $(OBJS)
	@echo "$(GREEN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -lm -lXext -lX11 -o $@ $(OBJS) $(LIBFT) $(MLX_LIB)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(OBJ_DIR)/%.o: srcs/%.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@ -I .

$(MLX_LIB):
	@echo "$(GREEN)Building MLX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) --silent >/dev/null 2>&1

$(LIBFT):
	@echo "$(GREEN)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --silent >/dev/null 2>&1

all: $(NAME)

clean:
	@echo "$(GREEN)Cleaning object files...$(RESET)"
	@$(MAKE) clean -C $(LIBFT_DIR) --silent >/dev/null 2>&1
	@$(MAKE) clean -C $(MLX_DIR) --silent >/dev/null 2>&1
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(GREEN)Full clean...$(RESET)"
	@$(MAKE) fclean -C $(LIBFT_DIR) --silent >/dev/null 2>&1
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

