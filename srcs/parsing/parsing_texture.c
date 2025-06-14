/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:44:30 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/14 13:44:08 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_xpm(char *file)
{
	int	i;

	i = ft_strlen(file) - 2;
	if ((file[i] != 'm' || file[i - 1] != 'p' \
		|| file[i - 2] != 'x' || file[i - 3] != '.'))
		return (msg_error("Textures must be .xpm\n"));
	return (1);
}

int	can_access_texture(t_data *data)
{
	if (!data->texture_path[NORTH] || access(data->texture_path[NORTH], F_OK) == -1 \
		|| access(data->texture_path[NORTH], R_OK) == -1)
		return (msg_error("Invalid texture path\n"));
	else if (!data->texture_path[SUD] || access(data->texture_path[SUD], F_OK) == -1 \
		|| access(data->texture_path[SUD], R_OK) == -1)
		return (msg_error("Invalid texture path\n"));
	else if (!data->texture_path[OUEST] || access(data->texture_path[OUEST], F_OK) == -1 \
		|| access(data->texture_path[OUEST], R_OK) == -1)
		return (msg_error("Invalid texture path\n"));
	else if (!data->texture_path[EST] || access(data->texture_path[EST], F_OK) == -1 \
		|| access(data->texture_path[EST], R_OK) == -1)
		return (msg_error("Invalid texture path\n"));
	return (1);
}

int	parse_texture(t_data *data, char *line)
{
	int		j;

	if (!is_xpm(line))
		return (0);
	j = 2;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = 0;
	j += 2;
	if (line[0] == 'N' && data->texture_path[NORTH] == NULL)
		data->texture_path[NORTH] = ft_strdup(&line[j]);
	else if (line[0] == 'S' && data->texture_path[SUD] == NULL)
		data->texture_path[SUD] = ft_strdup(&line[j]);
	else if (line[0] == 'W' && data->texture_path[OUEST] == NULL)
		data->texture_path[OUEST] = ft_strdup(&line[j]);
	else if (line[0] == 'E' && data->texture_path[EST] == NULL)
		data->texture_path[EST] = ft_strdup(&line[j]);
    data->p.pcheck++;
	return (1);
}