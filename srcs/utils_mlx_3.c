/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthol <mberthol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:26:39 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/19 21:09:54 by mberthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int	can_close_door(t_data *data, int door_x, int door_y)
{
	int	player_map_x;
	int	player_map_y;
	int	walkable;

	player_map_x = (int)data->player.x / TILE_SIZE;
	player_map_y = (int)data->player.y / TILE_SIZE;
	if (player_map_x == door_x && player_map_y == door_y)
		return (0);
	data->doormap[door_y][door_x] = '1';
	walkable = is_walkable(data, data->player.x, data->player.y);
	data->doormap[door_y][door_x] = '0';
	return (walkable);
}

/*static void	close_door(t_data *data, int mapx, int mapy)
{
	if (data->map[mapy - 1][mapx] == 'D' && data->doormap[mapy
		- 1][mapx] == '0')
			if (can_close_door(data, mapx, mapy - 1))
				data->doormap[mapy - 1][mapx] = '1';
	if (data->map[mapy + 1][mapx] == 'D' && data->doormap[mapy
		+ 1][mapx] == '0')
			if (can_close_door(data, mapx, mapy + 1))
				data->doormap[mapy + 1][mapx] = '1';
	if (data->map[mapy][mapx - 1] == 'D' && data->doormap[mapy][mapx
		- 1] == '0')
			if (can_close_door(data, mapx + 1, mapy))
				data->doormap[mapy][mapx - 1] = '1';
	if (data->map[mapy][mapx + 1] == 'D' && data->doormap[mapy][mapx
		+ 1] == '0')
			if (can_close_door(data, mapx + 1, mapy))
				data->doormap[mapy][mapx + 1] = '1';
}
static void	open_door(t_data *data, int mapx, int mapy)
{
	int			mapx;
	int			mapy;
	static int	key_pressed = 0;

	if (data->map[mapy - 1][mapx] == 'D' && data->doormap[mapy
		- 1][mapx] == '1')
			data->doormap[mapy - 1][mapx] = '0';
	if (data->map[mapy + 1][mapx] == 'D' && data->doormap[mapy
		+ 1][mapx] == '1')
			data->doormap[mapy + 1][mapx] = '0';
	if (data->map[mapy][mapx - 1] == 'D' && data->doormap[mapy][mapx
		- 1] == '1')
			data->doormap[mapy][mapx - 1] = '0';
	if (data->map[mapy][mapx + 1] == 'D' && data->doormap[mapy][mapx
		+ 1] == '1')
			data->doormap[mapy][mapx + 1] = '0';
}*/
void	handle_door(t_data *data)
{
	int			mapx;
	int			mapy;
	static int	key_pressed = 0;

	mapx = (int)data->player.x / TILE_SIZE;
	mapy = (int)data->player.y / TILE_SIZE;
	if (data->input[KEY_E] && !key_pressed)
	{
		key_pressed = 1;
		// open_door(data, mapx, mapy);
		// close_door(data, mapx, mapy);
		if (data->map[mapy - 1][mapx] == 'D' && data->doormap[mapy
			- 1][mapx] == '1')
			data->doormap[mapy - 1][mapx] = '0';
		else if (data->map[mapy + 1][mapx] == 'D' && data->doormap[mapy
			+ 1][mapx] == '1')
			data->doormap[mapy + 1][mapx] = '0';
		else if (data->map[mapy][mapx - 1] == 'D' && data->doormap[mapy][mapx
			- 1] == '1')
			data->doormap[mapy][mapx - 1] = '0';
		else if (data->map[mapy][mapx + 1] == 'D' && data->doormap[mapy][mapx
			+ 1] == '1')
			data->doormap[mapy][mapx + 1] = '0';
		else if (data->map[mapy - 1][mapx] == 'D' && data->doormap[mapy
			- 1][mapx] == '0')
		{
			if (can_close_door(data, mapx, mapy - 1))
				data->doormap[mapy - 1][mapx] = '1';
		}
		else if (data->map[mapy + 1][mapx] == 'D' && data->doormap[mapy
			+ 1][mapx] == '0')
		{
			if (can_close_door(data, mapx, mapy - 1))
				data->doormap[mapy + 1][mapx] = '1';
		}
		else if (data->map[mapy][mapx - 1] == 'D' && data->doormap[mapy][mapx
			- 1] == '0')
		{
			if (can_close_door(data, mapx, mapy - 1))
				data->doormap[mapy][mapx - 1] = '1';
		}
		else if (data->map[mapy][mapx + 1] == 'D' && data->doormap[mapy][mapx
			+ 1] == '0')
		{
			if (can_close_door(data, mapx, mapy - 1))
				data->doormap[mapy][mapx + 1] = '1';
		}
	}
	else if (!data->input[KEY_E])
		key_pressed = 0;
}
