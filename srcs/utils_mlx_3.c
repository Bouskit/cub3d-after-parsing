/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthol <mberthol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:26:39 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/14 16:32:01 by mberthol         ###   ########.fr       */
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

int	update_events(t_data *data)
{
	if (data->input[KEY_ESC])
		exit_data(data);
	handle_movement(data);
	handle_strafe(data);
	handle_rotation(data);
	return (0);
}
