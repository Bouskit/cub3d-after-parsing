/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:45:26 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/14 14:45:51 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void free_double(char **x)
{
    int i;

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