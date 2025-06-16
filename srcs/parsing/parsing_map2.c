/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:48:19 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/16 16:23:40 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	put_map_struct(t_data *data, int fd, char *line)
{
	int	j;

	j = 0;
	data->map = malloc(sizeof(char *) * (data->p.map_lines + 1));
	if (!data->map)
		return (msg_error("Malloc map error\n"));
	line = get_next_line(fd);
	while (line && line[0] != '1' && line[0] != ' ')
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = 0;
		data->map[j] = parsing_map(data, line);
		if (!data->map[j])
			return (free_double(data->map), msg_error("Map parsing error\n"));
		j++;
		line = get_next_line(fd);
	}
	data->map[data->p.map_lines] = NULL;
	close(fd);
	return (1);
}

int	count_line_map(t_data *data, int fd, char *line)
{
	char	*map;

	map = line;
	while (map)
	{
		if (map[0] == '1' || map[0] == ' ' || map[0] == '\n')
			data->p.map_lines++;
		free(map);
		map = get_next_line(fd);
	}
	close(fd);
	return (1);
}

int	second_check(t_data *data, int fd, char *line)
{
	if (data->p.pcheck != 6)
	{
		msg_error("Not 6 types of informations as expected\n");
		return (0);
	}
	if (!put_map_struct(data, fd, line))
		return (0);
	if (data->p.has_player != 1)
	{
		free_double(data->map);
		return (msg_error("No player in the map\n"));
	}
	if (!is_closed_map(data->map))
	{
		free_double(data->map);
		return (msg_error("Map not closed or have problem\n"));
	}
	close(fd);
	if (!can_access_texture(data))
	{
		free_double(data->map);
		return (0);
	}
	return (1);
}
