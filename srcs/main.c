/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:02:09 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/16 21:33:13 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	calculate_map_dimensions(t_data *data)
{
	int	i;
	int	max_len;
	int	len;

	data->map_haut = len_double(data->map);
	max_len = 0;
	i = 0;
	while (data->map[i])
	{
		len = ft_strlen(data->map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	data->map_larg = max_len;
}

int	init_data(t_data *data)
{
	int	i;

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
	calculate_map_dimensions(data);
	return (1);
}

int	main(int ac, char *av[])
{
	t_data	data;

	(void)ac;
	init_parsing(&data);
	if (!parsing(&data, av[1]))
		exit_data(&data);
	if (!init_data(&data))
		exit_data(&data);
	if (!init_game(&data))
	{
		printf("Erreur de init_game");
		return (1);
	}
	draw_background(&data);
	raycast(&data);
	draw_minimap(&data);
	mlx_hook(data.win, 17, 0, (int (*)())handle_cross, &data);
	mlx_hook(data.win, 2, 1L << 0, key_event, &data);
	mlx_hook(data.win, 3, 1L << 1, key_release, &data);
	mlx_loop_hook(data.mlx, main_loop, &data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
}
