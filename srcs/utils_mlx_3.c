/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:26:39 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/18 21:45:59 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	handle_movement(t_data *data)
{
	double	new_x;
	double	new_y;

	if (data->input[KEY_W])
	{
		new_x = data->player.x + cos(data->player.angle) * SPEED;
		new_y = data->player.y + sin(data->player.angle) * SPEED;
		if (is_walkable(data, new_x, data->player.y))
			data->player.x = new_x;
		if (is_walkable(data, data->player.x, new_y))
			data->player.y = new_y;
	}
	if (data->input[KEY_S])
	{
		new_x = data->player.x - cos(data->player.angle) * SPEED;
		new_y = data->player.y - sin(data->player.angle) * SPEED;
		if (is_walkable(data, new_x, data->player.y))
			data->player.x = new_x;
		if (is_walkable(data, data->player.x, new_y))
			data->player.y = new_y;
	}
}

static void	handle_strafe(t_data *data)
{
	double	new_x;
	double	new_y;

	if (data->input[KEY_A])
	{
		new_x = data->player.x + cos(data->player.angle - PI / 2) * SPEED;
		new_y = data->player.y + sin(data->player.angle - PI / 2) * SPEED;
		if (is_walkable(data, new_x, data->player.y))
			data->player.x = new_x;
		if (is_walkable(data, data->player.x, new_y))
			data->player.y = new_y;
	}
	if (data->input[KEY_D])
	{
		new_x = data->player.x + cos(data->player.angle + PI / 2) * SPEED;
		new_y = data->player.y + sin(data->player.angle + PI / 2) * SPEED;
		if (is_walkable(data, new_x, data->player.y))
			data->player.x = new_x;
		if (is_walkable(data, data->player.x, new_y))
			data->player.y = new_y;
	}
}

static void	handle_rotation(t_data *data)
{
	if (data->input[KEY_RIGHT])
	{
		data->player.angle += ROT_SPEED;
		if (data->player.angle >= 2 * PI)
			data->player.angle -= 2 * PI;
	}
	if (data->input[KEY_LEFT])
	{
		data->player.angle -= ROT_SPEED;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
	}
}

void init_doormap(t_data *data)
{
	int x;
	int y = 0;

	data->doormap = malloc(sizeof(char *) * (data->map_haut + 1));
	while (y < data->map_haut)
	{
		data->doormap[y] = malloc(sizeof(char) * (data->map_larg + 1));
		x = 0;
		while (x < data->map_larg)
		{
			if (data->map[y][x] == 'D')
				data->doormap[y][x] = '1';
			else 
				data->doormap[y][x] = data->map[y][x];
			x++;
		}
		data->doormap[y][data->map_larg] = '\0';
		y++;
	}
	data->doormap[y] = NULL;
}

static int can_close_door(t_data *data, int door_x, int door_y)
{
    int player_map_x = (int)data->player.x / TILE_SIZE;
    int player_map_y = (int)data->player.y / TILE_SIZE;
    
    // Ne pas fermer si le joueur est dans la case de la porte
    if (player_map_x == door_x && player_map_y == door_y)
        return (0);
        
    // Vérifier si le joueur serait bloqué après fermeture
    // Simuler la fermeture temporairement
    data->doormap[door_y][door_x] = '1';
    int walkable = is_walkable(data, data->player.x, data->player.y);
    data->doormap[door_y][door_x] = '0'; // Remettre l'état original
    
    return (walkable);
}

void handle_door(t_data *data)
{
	int mapx;
	int mapy;
	static int key_pressed = 0;

	mapx = (int)data->player.x / TILE_SIZE;
	mapy = (int)data->player.y / TILE_SIZE;
	if (data->input[KEY_E] && !key_pressed)
	{
		key_pressed = 1;
		if (data->map[mapy - 1][mapx] == 'D' && data->doormap[mapy - 1][mapx] == '1')
			data->doormap[mapy - 1][mapx] = '0';
		else if (data->map[mapy + 1][mapx] == 'D' && data->doormap[mapy + 1][mapx] == '1')
			data->doormap[mapy + 1][mapx] = '0';
		else if (data->map[mapy][mapx - 1] == 'D' && data->doormap[mapy][mapx - 1] == '1')
			data->doormap[mapy][mapx - 1] = '0';
		else if (data->map[mapy][mapx + 1] == 'D' && data->doormap[mapy][mapx + 1] == '1')
			data->doormap[mapy][mapx + 1] = '0';

		else if (data->map[mapy - 1][mapx] == 'D' && data->doormap[mapy - 1][mapx] == '0')
		{
			if (can_close_door(data, mapx, mapy - 1))
                data->doormap[mapy - 1][mapx] = '1';
		}
		else if (data->map[mapy + 1][mapx] == 'D' && data->doormap[mapy + 1][mapx] == '0')
		{
			if (can_close_door(data, mapx, mapy - 1))
                data->doormap[mapy + 1][mapx] = '1';
		}
		else if (data->map[mapy][mapx - 1] == 'D' && data->doormap[mapy][mapx - 1] == '0')
		{
			if (can_close_door(data, mapx, mapy - 1))
                data->doormap[mapy][mapx - 1] = '1';
		}
		else if (data->map[mapy][mapx + 1] == 'D' && data->doormap[mapy][mapx + 1] == '0')
		{
			if (can_close_door(data, mapx, mapy - 1))
                data->doormap[mapy][mapx + 1] = '1';
		}
	}
	else if (!data->input[KEY_E])
    {
        key_pressed = 0;
    }
}

int	update_events(t_data *data)
{
	if (data->input[KEY_ESC])
		exit_data(data);
	handle_movement(data);
	handle_strafe(data);
	handle_rotation(data);
	handle_door(data);
	return (0);
}
