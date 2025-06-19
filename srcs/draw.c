/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthol <mberthol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:00:02 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/17 21:17:44 by mberthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_background(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_LARG)
	{
		y = 0;
		while (y < WIN_HAUT)
		{
			if (y < WIN_HAUT / 2)
				put_pixel(data, x, y, data->p.sky_color);
			else
				put_pixel(data, x, y, data->p.ground_color);
			y++;
		}
		x++;
	}
}

void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if (i < 1 || i > TILE_SIZE - 1 || j < 1 || j > TILE_SIZE - 1)
				put_pixel(data, x + j, y + i, 0x000000);
			else
				put_pixel(data, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	redraw(t_data *data)
{
	draw_background(data);
	raycast(data);
	draw_minimap(data);
	draw_weapon_sprite(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
