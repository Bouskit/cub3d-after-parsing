/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:37:32 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/20 16:07:24 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	clamp_int(int value, int low, int high)
{
	if (value < low)
		return (low);
	if (value > high)
		return (high);
	return (value);
}

static double	normalize_angle(double angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

static t_wall	calculate_wall_params(double cor_dist, t_data *data)
{
	t_wall	wall;

	wall.hauteur = (int)(TILE_SIZE * data->dist_to_proj_plane / cor_dist);
	wall.top_og = (WIN_HAUT / 2) - (wall.hauteur / 2);
	wall.bottom = wall.top_og + wall.hauteur;
	wall.top = clamp_int(wall.top_og, 0, WIN_HAUT);
	wall.bottom = clamp_int(wall.bottom, 0, WIN_HAUT);
	return (wall);
}

void	raycast(t_data *data)
{
	int		i;
	double	angle;
	double	dist;
	double	cor_dist;
	t_wall	wall;

	i = 0;
	while (i < data->num_rays)
	{
		angle = data->player.angle - (FOV / 2.0) + i * (FOV / data->num_rays);
		angle = normalize_angle(angle);
		dist = cast_ray_dda(data, angle, i);
		cor_dist = dist * cos(angle - data->player.angle);
		if (cor_dist < 1.0)
			cor_dist = 1.0;
		wall = calculate_wall_params(cor_dist, data);
		draw_walls(data, wall, i);
		i++;
	}
}
