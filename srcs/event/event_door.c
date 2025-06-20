/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_door.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:26:39 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/20 16:35:23 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

int	*get_key_pressed(void)
{
	static int	key_pressed = 0;

	return (&key_pressed);
}

int	handle_open_door(t_data *data)
{
	int	mapx;
	int	mapy;

	mapx = (int)data->player.x / TILE_SIZE;
	mapy = (int)data->player.y / TILE_SIZE;
	if (data->map[mapy - 1][mapx] == 'D'
		&& data->doormap[mapy - 1][mapx] == '1')
		return (data->doormap[mapy - 1][mapx] = '0', 1);
	else if (data->map[mapy + 1][mapx] == 'D'
		&& data->doormap[mapy + 1][mapx] == '1')
		return (data->doormap[mapy + 1][mapx] = '0', 1);
	else if (data->map[mapy][mapx - 1] == 'D'
		&& data->doormap[mapy][mapx - 1] == '1')
		return (data->doormap[mapy][mapx - 1] = '0', 1);
	else if (data->map[mapy][mapx + 1] == 'D'
		&& data->doormap[mapy][mapx + 1] == '1')
		return (data->doormap[mapy][mapx + 1] = '0', 1);
	return (0);
}

void	handle_close_door(t_data *data, int mapx, int mapy)
{
	if (data->map[mapy - 1][mapx] == 'D'
		&& data->doormap[mapy - 1][mapx] == '0')
	{
		if (can_close_door(data, mapx, mapy - 1))
			data->doormap[mapy - 1][mapx] = '1';
	}
	else if (data->map[mapy + 1][mapx] == 'D'
		&& data->doormap[mapy + 1][mapx] == '0')
	{
		if (can_close_door(data, mapx, mapy + 1))
			data->doormap[mapy + 1][mapx] = '1';
	}
	else if (data->map[mapy][mapx - 1] == 'D'
		&& data->doormap[mapy][mapx - 1] == '0')
	{
		if (can_close_door(data, mapx - 1, mapy))
			data->doormap[mapy][mapx - 1] = '1';
	}
	else if (data->map[mapy][mapx + 1] == 'D'
		&& data->doormap[mapy][mapx + 1] == '0')
	{
		if (can_close_door(data, mapx + 1, mapy))
			data->doormap[mapy][mapx + 1] = '1';
	}
}

void	handle_door(t_data *data)
{
	int	*key_pressed;
	int	mapx;
	int	mapy;

	key_pressed = get_key_pressed();
	if (data->input[KEY_E] && !(*key_pressed))
	{
		*key_pressed = 1;
		mapx = (int)data->player.x / TILE_SIZE;
		mapy = (int)data->player.y / TILE_SIZE;
		if (!handle_open_door(data))
			handle_close_door(data, mapx, mapy);
	}
	else if (!data->input[KEY_E])
		*key_pressed = 0;
}
