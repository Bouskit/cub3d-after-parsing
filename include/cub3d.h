#ifndef CUB3D_H
#define CUB3D_H

#include "../lib/minilibx/mlx.h"
#include "../lib/libft_custom/libft.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>

#define TILE_SIZE 64
#define WIN_LARG 800
#define WIN_HAUT 800

#define PI 3.14159
#define SPEED 3
#define ROT_SPEED (PI / 100)

#define FOV (60 * (PI / 180))
#define WALL_DIST 0.25

#define NORTH 0
#define	SUD 1
#define OUEST 2 
#define EST 3

enum e_keys
{
    KEY_W = 0,
    KEY_S,
    KEY_A,
    KEY_D,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_ESC,
    KEY_UP,
    KEY_DOWN,
    KEY_TOTAL
};

typedef struct s_ray {
    double rayDirX;
    double rayDirY;
    int mapX;
    int mapY;
    double sideDistX;
    double sideDistY;
    double deltaDistX;
    double deltaDistY;
    int stepX;
    int stepY;
    int hit;
    int side;
} t_ray;

typedef struct s_wall {
    int hauteur;
    int top;
    int bottom;
    int top_og;
} t_wall;

typedef struct s_player
{
    double x;
    double y;
    double angle;
} t_player;

typedef struct s_texture
{
	void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
}	t_texture;

typedef struct s_parsing
{
    int pcheck;
    int sky_color;
    int ground_color;
    int map_lines;
    int has_player;
} t_parsing;

typedef struct s_data 
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;

    int map_larg;
    int map_haut;
    int num_rays;

    char **map;

    t_player player;

    int input[KEY_TOTAL];

    double dist_to_proj_plane;


	t_texture texture[4];
	char *texture_path[4];
    double  *wall_hit_x;
    int     *wall_hit_side;
	int *ray_direction;
    
    t_parsing p;

} t_data;

// TEXTURE

int	init_texture(t_data *data);
int	init_single_texture(t_data *data, int redirection, char *path);
void free_texture(t_data *data);
unsigned int get_texture_pixel(t_texture *texture, int x, int y);

//  DRAW

void    draw_background(t_data *data);
void    draw_square(t_data *data, int x, int y, int color);
void    redraw(t_data *data);

//  RAYCASTING

void raycast(t_data *data);
void draw_walls(t_data *data, t_wall wall, int i);

//DDA 

void init_dda(t_ray *ray, t_data *data, double ray_angle);
void perform_dda(t_ray *ray, t_data *data, int ray_index);
double compute_dda_result(t_ray *ray, t_data *data, int ray_index);
double cast_ray_dda(t_data *data, double ray_angle, int ray_index);


//  UTILS MLX

void	put_pixel(t_data *data, int x, int y, int color);
int	exit_data(t_data *data);
int	handle_cross(t_data *data);
int key_event(int key, t_data *data);
int	key_release(int key, t_data *data);
int	update_events(t_data *data);
int main_loop(void *args);

//  UTILS 
void free_double(char **x);
int	len_double(char **tab);

//PARSING

// PARSING COLOR
void	put_colors(t_data *data, char **line_colors, int boolean);
int	check_last_color(char *str);
int	parse_color2(t_data *data, int boolean, char **line_colors);
int	parse_color(t_data *data, char *line, int boolean);
//PARSING MAP
char	*parsing_map(t_data *data, char *line);
int	check_last_line(char **str);
int	check_first_line(char **str);
int	is_closed_map(char **str);
int	put_map_struct(t_data *data, int fd, char *line);
int	count_line_map(t_data *data, int fd, char *line);
int	second_check(t_data *data, int fd, char *line);
//PARSING TEXTURE
int	can_access_texture(t_data *data);
int	parse_texture(t_data *data, char *line);
//PARSING UTILS
int msg_error(char *str);
int	count_commas(char *line);
int	str_is_alpha(char *str);
int	check_space_or_void(char **str, int i, int j);
int	str_is_number(char *str);
//PARSING
char *before_map(t_data *data, int fd);
int parse_line(t_data *data, char *line);
int parsing(t_data *data, char *file);


#endif