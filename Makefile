NAME = cub3d

SRCS = srcs/draw.c \
		srcs/free_exit.c \
		srcs/init.c \
		srcs/texture.c \
		srcs/utils.c \
		srcs/main.c \
		srcs/event/event_door.c \
		srcs/event/event_mouse.c \
		srcs/event/event_utils.c \
		srcs/event/handle.c \
		srcs/minimap/minimap_player.c \
		srcs/minimap/minimap_walls.c \
		srcs/minimap/minimap.c \
		srcs/parsing/parsing_color.c \
		srcs/parsing/parsing_map.c \
		srcs/parsing/parsing_map2.c \
		srcs/parsing/parsing_texture.c \
		srcs/parsing/parsing_utils.c \
		srcs/parsing/parsing.c \
		srcs/raycasting/dda.c \
		srcs/raycasting/dda_2.c \
		srcs/raycasting/raycasting.c \
		srcs/raycasting/raycasting_2.c \
		srcs/weapon/weapon_utils.c \
		srcs/weapon/weapon.c \

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

