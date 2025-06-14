/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 14:27:22 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/14 14:31:21 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void init_dda(t_ray *ray, t_data *data, double ray_angle)
{
    ray->rayDirX = cos(ray_angle);
    ray->rayDirY = sin(ray_angle);
    ray->mapX = (int)(data->player.x / TILE_SIZE);
    ray->mapY = (int)(data->player.y / TILE_SIZE);
    ray->deltaDistX = fabs(1.0 / ray->rayDirX);
    ray->deltaDistY = fabs(1.0 / ray->rayDirY);
    if (ray->rayDirX < 0)
    {
        ray->stepX = -1;
        ray->sideDistX = (data->player.x / TILE_SIZE - ray->mapX) * ray->deltaDistX;
    }
    else
    {
        ray->stepX = 1;
        ray->sideDistX = (ray->mapX + 1.0 - data->player.x / TILE_SIZE) * ray->deltaDistX;
    }
    if (ray->rayDirY < 0)
    {
        ray->stepY = -1;
        ray->sideDistY = (data->player.y / TILE_SIZE - ray->mapY) * ray->deltaDistY;
    }
    else
    {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - data->player.y / TILE_SIZE) * ray->deltaDistY;
    }
    ray->hit = 0;
}

void perform_dda(t_ray *ray, t_data *data, int ray_index)
{
    while (ray->hit == 0)
    {
        if (ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX;
            ray->mapX += ray->stepX;
            ray->side = 0;
        }
        else
        {
            ray->sideDistY += ray->deltaDistY;
            ray->mapY += ray->stepY;
            ray->side = 1;
        }

        if (ray->mapY < 0 || ray->mapX < 0
            || ray->mapY >= data->map_haut || ray->mapX >= data->map_larg)
            break;

        if (data->map[ray->mapY][ray->mapX] == '1')
        {
            ray->hit = 1;
            if (ray->side == 0)
                data->ray_direction[ray_index] = (ray->stepX == 1) ? OUEST : EST;
            else
                data->ray_direction[ray_index] = (ray->stepY == 1) ? SUD : NORTH;
        }
    }
}

double compute_dda_result(t_ray *ray, t_data *data, int ray_index)
{
    double perpDist;
    double wall_x;
    if (ray->side == 0)
        perpDist = (ray->mapX - data->player.x / TILE_SIZE
                  + (1 - ray->stepX) / 2.0) / ray->rayDirX;
    else
        perpDist = (ray->mapY - data->player.y / TILE_SIZE
                  + (1 - ray->stepY) / 2.0) / ray->rayDirY;

    if (ray->side == 0)
        wall_x = data->player.y / TILE_SIZE + perpDist * ray->rayDirY;
    else
        wall_x = data->player.x / TILE_SIZE + perpDist * ray->rayDirX;
    wall_x -= floor(wall_x);

    data->wall_hit_x[ray_index] = wall_x;
    data->wall_hit_side[ray_index] = ray->side;

    return perpDist * TILE_SIZE;
}

double cast_ray_dda(t_data *data, double ray_angle, int ray_index)
{
    t_ray ray;
    init_dda(&ray, data, ray_angle);
    perform_dda(&ray, data, ray_index);
    return compute_dda_result(&ray, data, ray_index);
}
