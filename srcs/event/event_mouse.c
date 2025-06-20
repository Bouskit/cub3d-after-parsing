/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:14:59 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/20 16:06:51 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	inital_fonction(int center_x, int center_y, t_data *data)
{
	static int	inital = 0;

	if (!inital)
	{
		mlx_mouse_move(data->mlx, data->win, center_x, center_y);
		inital = 1;
		return (1);
	}
	return (0);
}

static void	if_abs_delta(t_data *data, int delta_x, int center_x, int center_y)
{
	if (ft_abs(delta_x) > 2)
	{
		data->player.angle += delta_x * 0.002;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI;
		if (data->player.angle >= 2 * PI)
			data->player.angle -= 2 * PI;
		mlx_mouse_move(data->mlx, data->win, center_x, center_y);
	}
}

int	mouse_move(int x, int y, void *param)
{
	int			delta_x;
	t_data		*data;
	int			center_x;
	int			center_y;

	data = (t_data *)param;
	(void)y;
	center_x = WIN_LARG / 2;
	center_y = WIN_HAUT / 2;
	if (inital_fonction(center_x, center_y, data))
		return (0);
	delta_x = x - center_x;
	if_abs_delta(data, delta_x, center_x, center_y);
	return (0);
}
