/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthol <mberthol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 21:10:54 by mberthol          #+#    #+#             */
/*   Updated: 2025/06/17 22:38:51 by mberthol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	init_weapon_sprites(t_data *data)
{
    char	*sprite_paths[3] = {
        "sprites/test1.xpm",
        "sprites/test2.xpm", 
        "sprites/test3.xpm"
    };
    int		i;

    i = 0;
    while (i < 3)
    {
        if (!init_weapon_sprite(data, i, sprite_paths[i]))
            return (0);
        i++;
    }
    return (1);
}

int	init_weapon_sprite(t_data *data, int index, char *path)
{
    int	hauteur;
    int	largeur;

    data->weapon_sprite[index].img = mlx_xpm_file_to_image(data->mlx, path,
            &largeur, &hauteur);
    if (!data->weapon_sprite[index].img)
        return (0);
    data->weapon_sprite[index].addr = mlx_get_data_addr(
            data->weapon_sprite[index].img,
            &data->weapon_sprite[index].bpp,
            &data->weapon_sprite[index].line_len,
            &data->weapon_sprite[index].endian);
    data->weapon_sprite[index].height = hauteur;
    data->weapon_sprite[index].width = largeur;
    return (1);
}

int is_dark_color(unsigned int color)
{
    unsigned char r = (color >> 16) & 0xFF;
    unsigned char g = (color >> 8) & 0xFF;
    unsigned char b = color & 0xFF;
    return (r < 30 && g < 30 && b < 30);
}

void	draw_weapon_sprite(t_data *data)
{
    int				sprite_x;
    int				sprite_y;
    int				x;
    int				y;
    unsigned int	color;
    int				current_sprite;
    static int		frame_counter = 0;
    int				scale = 1;

    frame_counter++;
    current_sprite = (frame_counter / 30) % 3;
    sprite_x = WIN_LARG - (data->weapon_sprite[current_sprite].width * scale) - 20;
    sprite_y = WIN_HAUT - (data->weapon_sprite[current_sprite].height * scale) + 50;
    
    y = 0;
    while (y < data->weapon_sprite[current_sprite].height)
    {
        x = 0;
        while (x < data->weapon_sprite[current_sprite].width)
        {
            color = get_texture_pixel(&data->weapon_sprite[current_sprite], x, y);
            if (!is_dark_color(color) && color != 0xFFFFFF)
            {
                int draw_y = 0;
                while (draw_y < scale)
                {
                    int draw_x = 0;
                    while (draw_x < scale)
                    {
                        put_pixel(data, sprite_x + (x * scale) + draw_x, 
                                 sprite_y + (y * scale) + draw_y, color);
                        draw_x++;
                    }
                    draw_y++;
                }
            }
            x++;
        }
        y++;
    }
}
