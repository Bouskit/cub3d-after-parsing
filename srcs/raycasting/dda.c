/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:27:22 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/20 16:07:20 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	init_dda_distances(t_ray *ray, t_data *data)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.x / TILE_SIZE - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.x / TILE_SIZE)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.y / TILE_SIZE - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.y / TILE_SIZE)
			* ray->delta_dist_y;
	}
}

void	init_dda(t_ray *ray, t_data *data, double ray_angle)
{
	ray->ray_dir_x = cos(ray_angle);
	ray->ray_dir_y = sin(ray_angle);
	ray->map_x = (int)(data->player.x / TILE_SIZE);
	ray->map_y = (int)(data->player.y / TILE_SIZE);
	ray->delta_dist_x = fabs(1.0 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1.0 / ray->ray_dir_y);
	init_dda_distances(ray, data);
	ray->hit = 0;
}

double	cast_ray_dda(t_data *data, double ray_angle, int ray_index)
{
	t_ray	ray;

	init_dda(&ray, data, ray_angle);
	perform_dda(&ray, data, ray_index);
	return (compute_dda_result(&ray, data, ray_index));
}
