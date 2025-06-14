/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthol <mberthol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:45:54 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/14 16:56:27 by mberthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	compute_dda_result(t_ray *ray, t_data *data, int ray_index)
{
	double	perp_dist;
	double	wall_x;

	if (ray->side == 0)
		perp_dist = (ray->map_x - data->player.x / TILE_SIZE + (1 - ray->step_x)
				/ 2.0) / ray->ray_dir_x;
	else
		perp_dist = (ray->map_y - data->player.y / TILE_SIZE + (1 - ray->step_y)
				/ 2.0) / ray->ray_dir_y;
	if (ray->side == 0)
		wall_x = data->player.y / TILE_SIZE + perp_dist * ray->ray_dir_y;
	else
		wall_x = data->player.x / TILE_SIZE + perp_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	data->wall_hit_x[ray_index] = wall_x;
	data->wall_hit_side[ray_index] = ray->side;
	return (perp_dist * TILE_SIZE);
}

static void	dda_step(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->map_x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->map_y += ray->step_y;
		ray->side = 1;
	}
}

static void	handle_wall_collision(t_ray *ray, t_data *data, int ray_index)
{
	if (data->map[ray->map_y][ray->map_x] == '1')
	{
		ray->hit = 1;
		if (ray->side == 0)
		{
			if (ray->step_x == 1)
				data->ray_direction[ray_index] = OUEST;
			else
				data->ray_direction[ray_index] = EST;
		}
		else
		{
			if (ray->step_y == 1)
				data->ray_direction[ray_index] = SUD;
			else
				data->ray_direction[ray_index] = NORTH;
		}
	}
}

void	perform_dda(t_ray *ray, t_data *data, int ray_index)
{
	while (ray->hit == 0)
	{
		dda_step(ray);
		if (ray->map_y < 0 || ray->map_x < 0 || ray->map_y >= data->map_haut
			|| ray->map_x >= data->map_larg)
			break ;
		handle_wall_collision(ray, data, ray_index);
	}
}
