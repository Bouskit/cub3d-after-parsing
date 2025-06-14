/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:50:27 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/14 14:43:09 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static int clamp_int(int value, int low, int high)
{
    if (value < low) 
        return (low);
    if (value > high) 
        return (high);
    return (value);
}

void raycast(t_data *data)
{
    int   i;
    double angle;
    double dist;
    double cor_dist;
    t_wall wall;

    i = 0;
    while (i < data->num_rays)
    {
        // 1) calcul de l’angle du rayon
        angle = data->player.angle - (FOV / 2.0) + i * (FOV / data->num_rays);
        if (angle < 0)       
            angle += 2 * PI;
        if (angle > 2 * PI)  
            angle -= 2 * PI;

        // 2) lancement DDA
        dist = cast_ray_dda(data, angle, i);

        // 3) correction fish-eye
        cor_dist = dist * cos(angle - data->player.angle);
        if (cor_dist < 1.0)
            cor_dist = 1.0;

        // 4) projection perspective
        wall.hauteur = (int)(TILE_SIZE * data->dist_to_proj_plane / cor_dist);
        wall.top_og = (WIN_HAUT / 2) - (wall.hauteur / 2);
        wall.bottom = wall.top_og + wall.hauteur;

        // 5) clipping vertical
        wall.top    = clamp_int(wall.top_og, 0, WIN_HAUT);
        wall.bottom = clamp_int(wall.bottom, 0, WIN_HAUT);

        // 6) dessin
        draw_walls(data, wall, i);

        i++;
    }
}

void draw_walls(t_data *data, t_wall wall, int i)
{
    int   y;
    int   tex_w = data->texture[data->ray_direction[i]].width;
    int   tex_h = data->texture[data->ray_direction[i]].height;
    double tex_x = data->wall_hit_x[i];

    // inversion pour certains côtés
    if (data->ray_direction[i] == NORTH || data->ray_direction[i] == EST)
        tex_x = 1.0 - tex_x;

    // coordonnée X dans la texture
    int texture_x = (int)(tex_x * tex_w);
    texture_x = clamp_int(texture_x, 0, tex_w - 1);

    // tracer chaque pixel vertical dans la portion visible
    y = wall.top;
    while (y < wall.bottom)
    {
        // offset depuis le top original du mur projeté
        double offset_in_wall = (double)(y - wall.top_og);
        double ratio          = offset_in_wall / (double)wall.hauteur;
        int texture_y         = (int)(ratio * tex_h);
        texture_y = clamp_int(texture_y, 0, tex_h - 1);

        unsigned int color = get_texture_pixel(
            &data->texture[data->ray_direction[i]],
            texture_x,
            texture_y
        );
        put_pixel(data, i, y, color);
        y++;
    }
}

