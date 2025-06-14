/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthol <mberthol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:33:04 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/14 16:16:20 by mberthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_player_angle(t_data *data, char dir)
{
	if (dir == 'N')
		data->player.angle = 3 * PI / 2.0;
	else if (dir == 'S')
		data->player.angle = PI / 2.0;
	else if (dir == 'W')
		data->player.angle = PI;
	else if (dir == 'E')
		data->player.angle = 0.0;
}

char	*parsing_map(t_data *data, char *line)
{
	static int	x = -1, y = 0;

	while (line[++x])
	{
		if (line[x] == 'N' || line[x] == 'W' || line[x] == 'S'
			|| line[x] == 'E')
		{
			data->p.has_player++;
			data->player.x = x * TILE_SIZE + TILE_SIZE / 2;
			data->player.y = y * TILE_SIZE + TILE_SIZE / 2;
			set_player_angle(data, line[x]);
			line[x] = '0';
		}
		if (line[x] != '1' && line[x] != '0' && line[x] != 'N' && line[x] != 'S'
			&& line[x] != 'W' && line[x] != 'E' && line[x] != '\n'
			&& line[x] != ' ')
			return (free(line), get_next_line(-1), NULL);
	}
	return (x = -1, y++, line);
}

int	check_last_line(char **str)
{
	int	j;

	j = -1;
	while (str[len_double(str) - 1][++j])
	{
		if (str[len_double(str) - 1][j] != '1' && str[len_double(str)
			- 1][j] != ' ')
			return (0);
	}
	return (1);
}

int	check_first_line(char **str)
{
	int	j;

	j = -1;
	while (str[0][++j])
	{
		if (str[0][j] != '1' && str[0][j] != ' ')
			return (0);
	}
	return (1);
}

int	is_closed_map(char **str)
{
	int	i;
	int	j;

	if (!check_first_line(str))
		return (0);
	if (!check_last_line(str))
		return (0);
	i = -1;
	while (str[++i])
	{
		j = 0;
		if (str[i][j] != '1' && str[i][j] != ' ')
			return (0);
		while (str[i][++j])
		{
			if (str[i][j] == '0' || str[i][j] == 'N' || str[i][j] == 'S'
				|| str[i][j] == 'W' || str[i][j] == 'E')
				if (check_space_or_void(str, i, j) == 0)
					return (0);
		}
	}
	return (1);
}
