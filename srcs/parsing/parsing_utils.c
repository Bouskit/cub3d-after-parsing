/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:18:30 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/13 23:11:46 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int msg_error(char *str)
{
    ft_putstr_fd("Error\n", 2);
    ft_putstr_fd(str, 2);
    return(0);
}

int	count_commas(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		return (0);
	return (1);
}

int	str_is_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	check_space_or_void(char **str, int i, int j)
{
	if ((int)ft_strlen(str[i - 1]) < j || (int)ft_strlen(str[i + 1]) < j)
		return (0);
	if (str[i][j - 1] == 0 || str[i][j + 1] == 0 \
		|| str[i - 1][j] == 0 || str[i + 1][j] == 0)
		return (0);
	if (str[i][j - 1] == ' ' || str[i][j + 1] == ' ' \
		|| str[i - 1][j] == ' ' || str[i + 1][j] == ' ')
		return (0);
	return (1);
}

int	str_is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}
