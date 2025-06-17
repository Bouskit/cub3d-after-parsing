/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthol <mberthol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 16:16:31 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/17 21:28:21 by mberthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

unsigned int	get_texture_pixel(t_texture *texture, int x, int y)
{
	char			*dest;
	unsigned int	color;

	color = 0;
	if (!texture || !texture->addr || x < 0 || x >= texture->width || y < 0
		|| y >= texture->height)
		return (0x000000);
	dest = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	color = *(unsigned int *)dest;
	return (color);
}

int	init_single_texture(t_data *data, int redirection, char *path)
{
	int	hauteur;
	int	largeur;

	data->texture[redirection].img = mlx_xpm_file_to_image(data->mlx, path,
			&hauteur, &largeur);
	if (!data->texture[redirection].img)
		return (0);
	data->texture[redirection].addr = mlx_get_data_addr
		(data->texture[redirection].img,
			&data->texture[redirection].bpp,
			&data->texture[redirection].line_len,
			&data->texture[redirection].endian);
	data->texture[redirection].height = hauteur;
	data->texture[redirection].width = largeur;
	return (1);
}

int	init_texture(t_data *data)
{
	if (!init_single_texture(data, NORTH, data->texture_path[NORTH]))
		return (0);
	if (!init_single_texture(data, SUD, data->texture_path[SUD]))
		return (0);
	if (!init_single_texture(data, OUEST, data->texture_path[OUEST]))
		return (0);
	if (!init_single_texture(data, EST, data->texture_path[EST]))
		return (0);
	return (1);
}

void	free_texture(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->texture[i].img)
			mlx_destroy_image(data->mlx, data->texture[i].img);
		free(data->texture_path[i]);
		i++;
	}
	i = 0;
    while (i < 3)
    {
        if (data->weapon_sprite[i].img)
        {
            mlx_destroy_image(data->mlx, data->weapon_sprite[i].img);
            data->weapon_sprite[i].img = NULL;
        }
        i++;
    }
}
