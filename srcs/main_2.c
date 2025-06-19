/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthol <mberthol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:56:56 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/17 21:32:35 by mberthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	init_game(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIN_LARG, WIN_HAUT, "CUB3D");
	data->img = mlx_new_image(data->mlx, WIN_LARG, WIN_HAUT);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len,
			&data->endian);
	ft_memset(data->input, 0, sizeof(data->input));
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
	data->p.has_player = 0;
	data->p.map_lines = 0;
	data->p.pcheck = 0;
	data->p.sky_color = 0;
	data->p.ground_color = 0;
	data->texture_path[NORTH] = NULL;
	data->texture_path[SUD] = NULL;
	data->texture_path[OUEST] = NULL;
	data->texture_path[EST] = NULL;
	data->texture_path[DOOR] = NULL;
	data->player.x = 0.0;
	data->player.y = 0.0;
	data->player.angle = 0.0;
}
