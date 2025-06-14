#include "../include/cub3d.h"

int init_data(t_data *data)
{
    int i;

    data->num_rays = WIN_LARG;
    data->ray_direction = malloc(sizeof(int) * data->num_rays);
    data->wall_hit_x = malloc(sizeof(double) * data->num_rays);
    data->wall_hit_side = malloc(sizeof(int) * data->num_rays);
    if (!data->ray_direction || !data->wall_hit_x || !data->wall_hit_side)
    {
        ft_printf("Erreur: échec d'allocation mémoire pour les rayons\n");
        return (0);
    }
    i = 0;
    while (i < data->num_rays)
    {
        data->ray_direction[i] = 0;
        data->wall_hit_x[i] = 0.0;
        data->wall_hit_side[i] = 0;
        i++;
    }
    data->dist_to_proj_plane = (WIN_LARG / 2.0) / tan(FOV / 2.0);


    data->map_haut = len_double(data->map);

    // map_larg : plus grande ligne (important si map non rectangulaire)
    int max_len = 0;
    for (int i = 0; data->map[i]; i++)
    {
        int len = ft_strlen(data->map[i]);
        if (len > max_len)
            max_len = len;
    }
    data->map_larg = max_len;

    return (1);
}

int init_game(t_data *data)
{
	data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIN_LARG, WIN_HAUT, "CUB3D");
    data->img = mlx_new_image(data->mlx, WIN_LARG, WIN_HAUT);
    data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, &data->endian);
	ft_memset(data->input, 0, sizeof(data->input));
    if(!init_texture(data))
	{
		free_texture(data);
		return (0);
	}
	return (1);
}

void init_parsing(t_data *data)
{
    data->p.has_player = 0;
    data->p.map_lines = 0;
    data->p.pcheck = 0;
    data->p.sky_color = 0;
    data->p.ground_color = 0;
    data->texture_path[NORTH] = NULL;
    data->texture_path[SUD] = NULL;
    data->texture_path[OUEST] = NULL;
    data->texture_path[EST] = NULL;
    data->player.x = 0.0;
    data->player.y = 0.0;
    data->player.angle = 0.0;
}

int main(int ac, char *av[])
{
    t_data data;

    (void)ac;
    init_parsing(&data);

    if (!parsing(&data, av[1]))
        return (1);
    
    if (!init_data(&data))
        exit_data(&data);
    
    if(!init_game(&data))
	{
		printf("Erreur de init_game");
		return (1);
	}
    draw_background(&data);
    raycast(&data);
    mlx_hook(data.win, 17, 0, (int (*)())handle_cross, &data);
	mlx_hook(data.win, 2, 1L << 0, key_event, &data);
    mlx_hook(data.win, 3, 1L << 1, key_release, &data);
    mlx_loop_hook(data.mlx, main_loop, &data);
    mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
    mlx_loop(data.mlx);
}
