/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:31:59 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/20 16:12:32 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	handle_movement(t_data *data)
{
	double	new_x;
	double	new_y;

	if (data->input[KEY_W])
	{
		new_x = data->player.x + cos(data->player.angle) * data->speed;
		new_y = data->player.y + sin(data->player.angle) * data->speed;
		if (is_walkable(data, new_x, data->player.y))
			data->player.x = new_x;
		if (is_walkable(data, data->player.x, new_y))
			data->player.y = new_y;
	}
	if (data->input[KEY_S])
	{
		new_x = data->player.x - cos(data->player.angle) * data->speed;
		new_y = data->player.y - sin(data->player.angle) * data->speed;
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
		new_x = data->player.x + cos(data->player.angle - PI / 2) * data->speed;
		new_y = data->player.y + sin(data->player.angle - PI / 2) * data->speed;
		if (is_walkable(data, new_x, data->player.y))
			data->player.x = new_x;
		if (is_walkable(data, data->player.x, new_y))
			data->player.y = new_y;
	}
	if (data->input[KEY_D])
	{
		new_x = data->player.x + cos(data->player.angle + PI / 2) * data->speed;
		new_y = data->player.y + sin(data->player.angle + PI / 2) * data->speed;
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

void	handle_run(t_data *data)
{
	if (data->input[KEY_RUN])
		data->speed = 6.0;
	else
		data->speed = 3.0;
}

int	update_events(t_data *data)
{
	if (data->input[KEY_ESC])
		exit_data(data);
	handle_run(data);
	handle_movement(data);
	handle_strafe(data);
	handle_rotation(data);
	handle_door(data);
	return (0);
}
