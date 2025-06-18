/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:16:19 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/18 21:28:34 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	free_raycasting_arrays(t_data *data)
{
	if (data && data->ray_direction)
	{
		free(data->ray_direction);
		data->ray_direction = NULL;
	}
	if (data && data->wall_hit_x)
	{
		free(data->wall_hit_x);
		data->wall_hit_x = NULL;
	}
	if (data && data->wall_hit_side)
	{
		free(data->wall_hit_side);
		data->wall_hit_side = NULL;
	}
}

static void	free_mlx_resources(t_data *data)
{
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}

int	exit_data(t_data *data)
{
	free_raycasting_arrays(data);
	free_texture(data);
	if (!data || !data->mlx)
		exit(EXIT_SUCCESS);
	free_double(data->map);
	free_double(data->doormap);
	free_mlx_resources(data);
	exit(EXIT_SUCCESS);
}

int	main_loop(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	update_events(data);
	redraw(data);
	return (0);
}
