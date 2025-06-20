/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 21:15:57 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/20 16:07:13 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	calculate_minimap_scale(t_data *data)
{
	int	minimap_width;
	int	minimap_height;
	int	scale;

	minimap_width = WIN_LARG / 3;
	minimap_height = WIN_HAUT / 3;
	scale = minimap_width / data->map_larg;
	if (minimap_height / data->map_haut < scale)
		scale = minimap_height / data->map_haut;
	if (scale < 1)
		scale = 1;
	return (scale);
}

void	draw_miniback(t_data *data)
{
	int	i;
	int	j;
	int	scale;
	int	actual_width;
	int	actual_height;

	scale = calculate_minimap_scale(data);
	actual_width = data->map_larg * scale;
	actual_height = data->map_haut * scale;
	i = 0;
	while (i < actual_height)
	{
		j = 0;
		while (j < actual_width)
		{
			put_pixel(data, j, i, 0xA90807);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	draw_miniback(data);
	draw_miniwalls(data);
	draw_miniplayer(data);
}
