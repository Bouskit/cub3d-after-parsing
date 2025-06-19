/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthol <mberthol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:10:54 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/19 21:14:49 by mberthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	process_pixel(t_data *data, t_sprite_draw *draw, int x, int y)
{
	unsigned int	color;
	int				draw_x;
	int				draw_y;

	color = get_texture_pixel(&data->weapon_sprite[draw->current_sprite], x, y);
	if (!is_dark_color(color) && color != 0xFFFFFF)
	{
		draw_y = 0;
		while (draw_y < draw->scale)
		{
			draw_x = 0;
			while (draw_x < draw->scale)
			{
				put_pixel(data, draw->sprite_x + (x * draw->scale) + draw_x,
					draw->sprite_y + (y * draw->scale) + draw_y, color);
				draw_x++;
			}
			draw_y++;
		}
	}
}

static void	draw_sprite_row(t_data *data, t_sprite_draw *draw, int y)
{
	int	x;

	x = 0;
	while (x < data->weapon_sprite[draw->current_sprite].width)
	{
		process_pixel(data, draw, x, y);
		x++;
	}
}

static void	init_sprite_draw(t_sprite_draw *draw, t_data *data,
		int frame_counter)
{
	draw->scale = 1;
	draw->current_sprite = (frame_counter / 30) % 3;
	draw->sprite_x = WIN_LARG - (data->weapon_sprite[draw->current_sprite].width
			* draw->scale) - 20;
	draw->sprite_y = WIN_HAUT
		- (data->weapon_sprite[draw->current_sprite].height * draw->scale) + 50;
}

void	draw_weapon_sprite(t_data *data)
{
	t_sprite_draw	draw;
	static int		frame_counter = 0;
	int				y;

	frame_counter++;
	init_sprite_draw(&draw, data, frame_counter);
	y = 0;
	while (y < data->weapon_sprite[draw.current_sprite].height)
	{
		draw_sprite_row(data, &draw, y);
		y++;
	}
}
