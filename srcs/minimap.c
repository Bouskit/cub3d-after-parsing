/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 21:32:36 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/16 22:47:45 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void draw_minimap(t_data *data)
{
    draw_miniback(data);
    draw_miniwalls(data);
    draw_miniplayer(data);
    draw_minifov(data);
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
                put_pixel(data, player_mini_x + j, player_mini_y + i, 0xFF0000);
            j++;
        }
        i++;
    }
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
            put_pixel(data, j, i, 0x404040);
            j++;
        }
        i++;
    }
}

void draw_miniwalls(t_data *data)
{
    int i;
    int j;
    int mini_x;
    int mini_y;
    int scale;

    scale = calculate_minimap_scale(data);

    i = 0;
    while (i < data->map_haut)
    {
        j = 0;
        while (j < data->map_larg && data->map[i])
        {
            if (j < (int)ft_strlen(data->map[i]) && data->map[i][j] == '1')
            {
                mini_y = 0;
                while (mini_y < scale)
                {
                    mini_x = 0;
                    while (mini_x < scale)
                    {
                        put_pixel(data, j * scale + mini_x, i * scale + mini_y, 0x000000);
                        mini_x++;
                    }
                    mini_y++;
                }
            }
            j++;
        }
        i++;
    }
}

void draw_minifov(t_data *data)
{
    int scale;
    int k;
    int w;
    int line_x;
    int line_y;

    scale = calculate_minimap_scale(data);
    if (scale < 10)
        scale = 10;
    k = 0;
    while (k < scale)
    {
        w = -2;
        while (w <= 2)
        {
            line_x = (int)(data->player.x / TILE_SIZE) * scale + (int)(cos(data->player.angle) * k) + 
                     (int)(cos(data->player.angle + PI/2) * w);
            line_y = (int)(data->player.y / TILE_SIZE) * scale + (int)(sin(data->player.angle) * k) + 
                     (int)(sin(data->player.angle + PI/2) * w);
            if (line_x >= 0 && line_y >= 0 && 
                line_x < data->map_larg * scale && 
                line_y < data->map_haut * scale)
            {
                put_pixel(data, line_x, line_y, 0xFF0000);
            }
            w++;
        }
        k++;
    }
}