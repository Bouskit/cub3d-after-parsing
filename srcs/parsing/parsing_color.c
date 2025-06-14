/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthol <mberthol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:43:56 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/14 16:10:28 by mberthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	rgb_to_int(char **line)
{
	return (ft_atoi(line[0]) << 16 | ft_atoi(line[1]) << 8
		| ft_atoi(line[2]) | 255 << 24);
}

void	put_colors(t_data *data, char **line_colors, int boolean)
{
	data->p.pcheck++;
	if (boolean == 1)
		data->p.ground_color = rgb_to_int(line_colors);
	else
		data->p.sky_color = rgb_to_int(line_colors);
	free_double(line_colors);
}

int	check_last_color(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			j++;
		i++;
	}
	if (j > 3)
		return (1);
	return (0);
}

int	parse_color2(t_data *data, int boolean, char **line_colors)
{
	int	color;
	int	i;

	i = -1;
	while (line_colors[++i])
	{
		if (!str_is_number(line_colors[i]))
			return (free_double(line_colors),
				msg_error("Colors must be only numbers\n"));
		color = ft_atoi(line_colors[i]);
		if (color < 0 || color > 255)
			return (free_double(line_colors),
				msg_error("Colors must contain values 0 < > 255\n"));
	}
	put_colors(data, line_colors, boolean);
	return (1);
}

int	parse_color(t_data *data, char *line, int boolean)
{
	char	**line_colors;

	if (!count_commas(line))
		return (msg_error("Invalid commas in the color\n"));
	line += 2;
	line_colors = ft_split(line, ',');
	if (line_colors == NULL)
		return (msg_error("Color malloc error\n"));
	if (len_double(line_colors) != 3)
		return (free_double(line_colors), msg_error("Color size/n"));
	if (check_last_color(*line_colors))
		return (free_double(line_colors),
			msg_error("Invalid color (Too many values)\n"));
	return (parse_color2(data, boolean, line_colors));
}
