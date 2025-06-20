/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:49:12 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/20 16:07:32 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	init_weapon_sprites(t_data *data)
{
	char	*sprite_paths[3];
	int		i;

	i = 0;
	sprite_paths[0] = "sprites/test1.xpm";
	sprite_paths[1] = "sprites/test2.xpm";
	sprite_paths[2] = "sprites/test3.xpm";
	while (i < 3)
	{
		if (!init_weapon_sprite(data, i, sprite_paths[i]))
			return (0);
		i++;
	}
	return (1);
}

int	init_weapon_sprite(t_data *data, int index, char *path)
{
	int	hauteur;
	int	largeur;

	data->weapon_sprite[index].img = mlx_xpm_file_to_image(data->mlx, path,
			&largeur, &hauteur);
	if (!data->weapon_sprite[index].img)
		return (0);
	data->weapon_sprite[index].addr = mlx_get_data_addr(
			data->weapon_sprite[index].img,
			&data->weapon_sprite[index].bpp,
			&data->weapon_sprite[index].line_len,
			&data->weapon_sprite[index].endian);
	data->weapon_sprite[index].height = hauteur;
	data->weapon_sprite[index].width = largeur;
	return (1);
}

int	is_dark_color(unsigned int color)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	return (r < 30 && g < 30 && b < 30);
}
