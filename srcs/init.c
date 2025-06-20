/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:56:56 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/20 15:53:34 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_doormap(t_data *data)
{
	int	x;
	int	y;

	y = 0;
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

int	init_game(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_LARG, WIN_HAUT, "CUB3D");
	data->img = mlx_new_image(data->mlx, WIN_LARG, WIN_HAUT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len,
			&data->endian);
	if (!init_texture(data))
	{
		free_texture(data);
		return (0);
	}
	if (!init_weapon_sprites(data))
	{
		printf("Erreur: impossible de charger les sprites d'arme\n");
		free_texture(data);
		return (0);
	}
	return (1);
}

void	init_parsing(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->speed = 3.0;
}
