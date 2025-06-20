/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:50:27 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/20 16:07:28 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static t_tex_params	init_texture_params(t_data *data, int i)
{
	t_tex_params	params;

	params.tex_w = data->texture[data->ray_direction[i]].width;
	params.tex_h = data->texture[data->ray_direction[i]].height;
	params.tex_x = data->wall_hit_x[i];
	if (data->ray_direction[i] == NORTH || data->ray_direction[i] == EST)
		params.tex_x = 1.0 - params.tex_x;
	params.texture_x = (int)(params.tex_x * params.tex_w);
	params.texture_x = clamp_int(params.texture_x, 0, params.tex_w - 1);
	return (params);
}

static void	draw_pixel_line(t_data *data, t_wall wall, t_tex_params params,
		int i)
{
	int				y;
	double			offset_in_wall;
	double			ratio;
	int				texture_y;
	unsigned int	color;

	y = wall.top;
	while (y < wall.bottom)
	{
		offset_in_wall = (double)(y - wall.top_og);
		ratio = offset_in_wall / (double)wall.hauteur;
		texture_y = (int)(ratio * params.tex_h);
		texture_y = clamp_int(texture_y, 0, params.tex_h - 1);
		color = get_texture_pixel(&data->texture[data->ray_direction[i]],
				params.texture_x, texture_y);
		put_pixel(data, i, y, color);
		y++;
	}
}

void	draw_walls(t_data *data, t_wall wall, int i)
{
	t_tex_params	params;

	params = init_texture_params(data, i);
	draw_pixel_line(data, wall, params, i);
}
