/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthol <mberthol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:17:56 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/19 17:37:31 by mberthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_release(int key, t_data *data)
{
	if (key == 65307)
		data->input[KEY_ESC] = 0;
	else if (key == 'w')
		data->input[KEY_W] = 0;
	else if (key == 'a')
		data->input[KEY_A] = 0;
	else if (key == 's')
		data->input[KEY_S] = 0;
	else if (key == 'd')
		data->input[KEY_D] = 0;
	else if (key == 65361)
		data->input[KEY_LEFT] = 0;
	else if (key == 65363)
		data->input[KEY_RIGHT] = 0;
	else if (key == 65362)
		data->input[KEY_UP] = 0;
	else if (key == 65364)
		data->input[KEY_DOWN] = 0;
	else if (key == 'e')
		data->input[KEY_E] = 0;
	return (0);
}

int	key_event(int key, t_data *data)
{
	if (key == 65307)
		data->input[KEY_ESC] = 1;
	else if (key == 'w')
		data->input[KEY_W] = 1;
	else if (key == 'a')
		data->input[KEY_A] = 1;
	else if (key == 's')
		data->input[KEY_S] = 1;
	else if (key == 'd')
		data->input[KEY_D] = 1;
	else if (key == 65361)
		data->input[KEY_LEFT] = 1;
	else if (key == 65363)
		data->input[KEY_RIGHT] = 1;
	else if (key == 65362)
		data->input[KEY_UP] = 1;
	else if (key == 65364)
		data->input[KEY_DOWN] = 1;
	else if (key == 'e')
		data->input[KEY_E] = 1;
	return (0);
}

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < WIN_LARG && y >= 0 && y < WIN_HAUT)
	{
		pixel = data->addr + (y * data->line_len + x * (data->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

int	handle_cross(t_data *data)
{
	exit_data(data);
	return (0);
}

int	is_walkable(t_data *data, double x, double y)
{
	int		map_x;
	int		map_y;
	double	frac_x;
	double	frac_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	frac_x = (x / TILE_SIZE) - map_x;
	frac_y = (y / TILE_SIZE) - map_y;
	if (data->doormap[map_y][map_x] == '1')
		return (0);
	if (frac_x > 1.0 - WALL_DIST && data->doormap[map_y][map_x + 1]
			== '1' && map_x + 1 < data->map_larg)
		return (0);
	if (frac_x < WALL_DIST && data->doormap[map_y][map_x - 1]
			== '1' && map_x - 1 >= 0)
		return (0);
	if (frac_y > 1.0 - WALL_DIST && data->doormap[map_y + 1][map_x]
			== '1' && map_y + 1 < data->map_haut)
		return (0);
	if (frac_y < WALL_DIST && data->doormap[map_y - 1][map_x]
			== '1' && map_y - 1 >= 0)
		return (0);
	return (1);
}
