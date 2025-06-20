/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:45:26 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/20 15:57:25 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < WIN_LARG && y >= 0 && y < WIN_HAUT)
	{
		pixel = data->addr + (y * data->line_len + x * (data->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

void	free_double(char **x)
{
	int	i;

	i = 0;
	while (x[i])
	{
		free(x[i]);
		i++;
	}
	free(x);
}

int	len_double(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}
