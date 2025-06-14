
NAME = cub3d

SRCS = srcs/main.c \
		srcs/utils_mlx.c \
		srcs/raycasting.c \
		srcs/draw.c \
		srcs/texture.c \
		srcs/dda.c \
		srcs/utils.c \
		srcs/parsing/parsing_color.c \
		srcs/parsing/parsing_map.c \
		srcs/parsing/parsing_map2.c \
		srcs/parsing/parsing_texture.c \
		srcs/parsing/parsing_utils.c \
		srcs/parsing/parsing.c \

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./lib/libft_custom
MLX_DIR = ./lib/minilibx

LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

$(NAME): $(MLX_LIB) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -lm -lXext -lX11 -o $@ $(OBJS) $(LIBFT) $(MLX_LIB)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I .

all: $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(MAKE) clean -C $(MLX_DIR)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
