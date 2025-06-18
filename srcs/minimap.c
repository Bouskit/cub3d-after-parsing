/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:32:36 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/18 22:05:02 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_minimap(t_data *data)
{
    draw_miniback(data);
    draw_miniwalls(data);
    draw_miniplayer(data);
}

static void draw_miniline(t_data *data, int scale, int player_mini_x, int player_mini_y)
{
    int i;
    int dx;
    int dy;

    i = 0;
    while (i < scale * 2)
    {
        dx = (int)(cos(data->player.angle) * i);
        dy = (int)(sin(data->player.angle) * i);
        put_pixel(data, player_mini_x + dx, player_mini_y + dy, 0xFFFFFF);
        i++;
    }
}

void draw_miniplayer(t_data *data)
{
    int scale;
    int player_mini_x;
    int player_mini_y;
    int player_size;
    int i;
    int j;

    scale = calculate_minimap_scale(data);
    player_mini_x = (int)(data->player.x / TILE_SIZE) * scale;
    player_mini_y = (int)(data->player.y / TILE_SIZE) * scale;
    player_size = scale / 4;
    if (player_size < 2)
        player_size = 2;
    i = -player_size;
    while (i <= player_size)
    {
        j = -player_size;
        while (j <= player_size)
        {
            if (player_mini_x + j >= 0 && player_mini_y + i >= 0)
                put_pixel(data, player_mini_x + j, player_mini_y + i, 0xFFFFFF);
            j++;
        }
        i++;
    }
    draw_miniline(data, scale, player_mini_x, player_mini_y);
}

int calculate_minimap_scale(t_data *data)
{
    int minimap_width;
    int minimap_height;
    int scale;

    minimap_width = WIN_LARG / 3;
    minimap_height = WIN_HAUT / 3;
    scale = minimap_width / data->map_larg;
    if (minimap_height / data->map_haut < scale)
        scale = minimap_height / data->map_haut;
    if (scale < 1)
        scale = 1;
    return (scale);
}

void draw_miniback(t_data *data)
{
    int i;
    int j;
    int scale;
    int actual_width;
    int actual_height;

    scale = calculate_minimap_scale(data);
    actual_width = data->map_larg * scale;
    actual_height = data->map_haut * scale;
    i = 0;
    while (i < actual_height)
    {
        j = 0;
        while (j < actual_width)
        {
            put_pixel(data, j, i, 0xA90807);
            j++;
        }
        i++;
    }
}

static unsigned int get_minimap_color(t_data *data, int map_y, int map_x)
{
    if (data->map[map_y][map_x] == '1')
        return (0x000000); // Mur - noir
    else if (data->map[map_y][map_x] == 'D')
    {
        if (data->doormap[map_y][map_x] == '1')
            return (0xFF0000); // Porte fermée - rouge
        else
            return (0x00FF00); // Porte ouverte - vert
    }
    return (0); // Espace vide - pas de couleur
}

static void draw_minimap_cell(t_data *data, int j, int i, int scale, unsigned int color)
{
    int mini_x;
    int mini_y;

    mini_y = 0;
    while (mini_y < scale)
    {
        mini_x = 0;
        while (mini_x < scale)
        {
            put_pixel(data, j * scale + mini_x, i * scale + mini_y, color);
            mini_x++;
        }
        mini_y++;
    }
}

void draw_miniwalls(t_data *data)
{
    int i;
    int j;
    int scale;
    unsigned int color;
    char cell_type;

    scale = calculate_minimap_scale(data);

    i = 0;
    while (i < data->map_haut)
    {
        j = 0;
        while (j < data->map_larg && data->map[i])
        {
            if (j < (int)ft_strlen(data->map[i]))
            {
                cell_type = data->map[i][j];
                // On dessine seulement si c'est un mur ou une porte
                if (cell_type == '1' || cell_type == 'D')
                {
                    color = get_minimap_color(data, i, j);
                    draw_minimap_cell(data, j, i, scale, color);
                }
            }
            j++;
        }
        i++;
    }
}
