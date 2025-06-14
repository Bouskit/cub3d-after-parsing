/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:14:05 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/13 22:47:00 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int is_pointcub(char *file)
{
    int i;

    i = ft_strlen(file) - 1;
    if (file[i] != 'b' || file[i - 1] != 'u' \
		|| file[i - 2] != 'c' || file[i - 3] != '.')
		return (0);
	return (1);
}

char *before_map(t_data *data, int fd)
{
    char *line;

    line = get_next_line(fd);
    while (line && line[0] != '1' && line[0] != ' ')
    {
        if (line[0] != '\n')
        {
            if (!parse_line(data, line))
            {
                close(fd);
                free(line);
                get_next_line(-1);
                return (NULL);
            }
        }
        free(line);
        line = get_next_line(fd);
    }
    if (!line)
        close(fd);
    return (line);
}

int parse_line(t_data *data, char *line)
{
    int tmp;

    tmp = 0;
    if (line[0] == 'N' && line[1] == 'O')
		tmp = parse_texture(data, line);
	else if (line[0] == 'S' && line[1] == 'O')
		tmp = parse_texture(data, line);
	else if (line[0] == 'W' && line[1] == 'E')
		tmp = parse_texture(data, line);
	else if (line[0] == 'E' && line[1] == 'A')
		tmp = parse_texture(data, line);
	else if (line[0] == 'F' && line[1] == ' ')
		tmp = parse_color(data, line, 1);
	else if (line[0] == 'C' && line[1] == ' ')
		tmp = parse_color(data, line, 0);
	else
		return (msg_error("Invalid line in the file\n"));
	if (tmp == 0)
		return (0);
    return (1);
}


int parsing(t_data *data, char *file)
{
    int fd;
    char *line;

    if (!is_pointcub(file))
        return (msg_error("Map is not a .cub\n"));
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (msg_error("Cannot open the file\n"));
    line = before_map(data, fd);
    if (!line)
        return (msg_error("Invalid map\n"));
    if (!count_line_map(data, fd, line))
        return (msg_error("Invalid map\n"));
    fd = open(file, O_RDONLY);
    if (!second_check(data, fd, line))
    {
        close(fd);
        return (0);
    }
    close(fd);
    return (1);
}