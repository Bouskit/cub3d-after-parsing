/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:32:36 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/20 16:07:09 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static unsigned int	get_minimap_color(t_data *data, int map_y, int map_x)
{
	if (data->map[map_y][map_x] == '1')
		return (0x000000);
	else if (data->map[map_y][map_x] == 'D')
	{
		if (data->doormap[map_y][map_x] == '1')
			return (0xFF0000);
		else
			return (0x00FF00);
	}
	return (0);
}

static void	draw_cell_pixels(t_data *data, int j, int i, t_minimap *mini)
{
	int	mini_x;
	int	mini_y;

	mini_y = 0;
	while (mini_y < mini->scale)
	{
		mini_x = 0;
		while (mini_x < mini->scale)
		{
			put_pixel(data, j * mini->scale + mini_x, i * mini->scale + mini_y,
				mini->color);
			mini_x++;
		}
		mini_y++;
	}
}

static void	process_map_cell(t_data *data, int i, int j, t_minimap *mini)
{
	if (j < (int)ft_strlen(data->map[i]))
	{
		mini->cell_type = data->map[i][j];
		if (mini->cell_type == '1' || mini->cell_type == 'D')
		{
			mini->color = get_minimap_color(data, i, j);
			draw_cell_pixels(data, j, i, mini);
		}
	}
}

void	draw_miniwalls(t_data *data)
{
	int			i;
	int			j;
	t_minimap	mini;

	mini.scale = calculate_minimap_scale(data);
	i = 0;
	while (i < data->map_haut)
	{
		j = 0;
		while (j < data->map_larg && data->map[i])
		{
			process_map_cell(data, i, j, &mini);
			j++;
		}
		i++;
	}
}
