/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthol <mberthol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:19:47 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/19 21:23:48 by mberthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	draw_miniline(t_data *data, int scale, int player_x, int player_y)
{
	int	i;
	int	dx;
	int	dy;

	i = 0;
	while (i < scale * 2)
	{
		dx = (int)(cos(data->player.angle) * i);
		dy = (int)(sin(data->player.angle) * i);
		put_pixel(data, player_x + dx, player_y + dy, 0xFFFFFF);
		i++;
	}
}

static void	draw_player_square(t_data *data, int x, int y, int size)
{
	int	i;
	int	j;

	i = -size;
	while (i <= size)
	{
		j = -size;
		while (j <= size)
		{
			if (x + j >= 0 && y + i >= 0)
				put_pixel(data, x + j, y + i, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	draw_miniplayer(t_data *data)
{
	int	scale;
	int	player_x;
	int	player_y;
	int	size;

	scale = calculate_minimap_scale(data);
	player_x = (int)(data->player.x / TILE_SIZE) * scale;
	player_y = (int)(data->player.y / TILE_SIZE) * scale;
	size = scale / 4;
	if (size < 2)
		size = 2;
	draw_player_square(data, player_x, player_y, size);
	draw_miniline(data, scale, player_x, player_y);
}
