/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 18:16:19 by bboukach          #+#    #+#             */
/*   Updated: 2025/06/14 14:33:51 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < WIN_LARG && y >= 0 && y < WIN_HAUT)
	{
		pixel = data->addr + (y * data->line_len + x * (data->bpp / 8));
		*(unsigned int *)pixel = color;
	}
}

int	exit_data(t_data *data)
{
	
	if (data && data->ray_direction)
	{
		free(data->ray_direction);
		data->ray_direction = NULL;
	}
	
	if (data && data->wall_hit_x)
	{
		free(data->wall_hit_x);
		data->wall_hit_x = NULL;
	}
	
	if (data && data->wall_hit_side)
	{
		free(data->wall_hit_side);
		data->wall_hit_side = NULL;
	}
	
	// Code existant pour libérer les autres ressources
	if (!data || !data->mlx)
		exit(EXIT_SUCCESS);
	free_double(data->map);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	exit(EXIT_SUCCESS);
}

int	handle_cross(t_data *data)
{
	exit_data(data);
	return (0);
}

int key_event(int key, t_data *data)
{
	if (key == 65307) // ESC
		data->input[KEY_ESC] = 1;
	else if (key == 'w')
		data->input[KEY_W] = 1;
	else if (key == 'a')
		data->input[KEY_A] = 1;
	else if (key == 's')
		data->input[KEY_S] = 1;
	else if (key == 'd')
		data->input[KEY_D] = 1;
	else if (key == 65361)
		data->input[KEY_LEFT] = 1;
	else if (key == 65363)
		data->input[KEY_RIGHT] = 1;
	else if (key == 65362)
		data->input[KEY_UP] = 1;
	else if (key == 65364)
		data->input[KEY_DOWN] = 1;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == 65307)
		data->input[KEY_ESC] = 0;
	else if (key == 'w')
		data->input[KEY_W] = 0;
	else if (key == 'a')
		data->input[KEY_A] = 0;
	else if (key == 's')
		data->input[KEY_S] = 0;
	else if (key == 'd')
		data->input[KEY_D] = 0;
	else if (key == 65361)
		data->input[KEY_LEFT] = 0;
	else if (key == 65363)
		data->input[KEY_RIGHT] = 0;
	else if (key == 65362)
		data->input[KEY_UP] = 0;
	else if (key == 65364)
		data->input[KEY_DOWN] = 0;
	return (0);
}

static int is_walkable(t_data *data, double x, double y)
{
	int mapX;
	int mapY;
	double fracX;
	double fracY;

	mapX = (int)(x / TILE_SIZE);
	mapY = (int)(y / TILE_SIZE);
	fracX = (x / TILE_SIZE) - mapX;
	fracY = (y / TILE_SIZE) - mapY;
	if (data->map[mapY][mapX] == '1')
		return 0;
	if (fracX > 1.0 - WALL_DIST && data->map[mapY][mapX + 1] == '1') // droite
		return 0;
	if (fracX < WALL_DIST && data->map[mapY][mapX - 1] == '1') // gauche
		return 0;
	if (fracY > 1.0 - WALL_DIST && data->map[mapY + 1][mapX] == '1') // bas
		return 0;
	if (fracY < WALL_DIST && data->map[mapY - 1][mapX] == '1') // haut
		return 0;
	return 1;
}

int	update_events(t_data *data)
{

	double new_x;
	double new_y;

	if (data->input[KEY_ESC])
		exit_data(data);

	if (data->input[KEY_W])
	{
		new_x = data->player.x + cos(data->player.angle) * SPEED;
		new_y = data->player.y + sin(data->player.angle) * SPEED;

		if (is_walkable(data, new_x, data->player.y))
			data->player.x = new_x;
		if (is_walkable(data, data->player.x, new_y))
			data->player.y = new_y;
	}

	if (data->input[KEY_S])
	{
		new_x = data->player.x - cos(data->player.angle) * SPEED;
		new_y = data->player.y - sin(data->player.angle) * SPEED;

		if (is_walkable(data, new_x, data->player.y))
			data->player.x = new_x;
		if (is_walkable(data, data->player.x, new_y))
			data->player.y = new_y;
	}

	if (data->input[KEY_A])
	{
		new_x = data->player.x + cos(data->player.angle - PI / 2) * SPEED;
		new_y = data->player.y + sin(data->player.angle - PI / 2) * SPEED;

		if (is_walkable(data, new_x, data->player.y))
			data->player.x = new_x;
		if (is_walkable(data, data->player.x, new_y))
			data->player.y = new_y;
	}

	if (data->input[KEY_D])
	{
		new_x = data->player.x + cos(data->player.angle + PI / 2) * SPEED;
		new_y = data->player.y + sin(data->player.angle + PI / 2) * SPEED;

		if (is_walkable(data, new_x, data->player.y))
			data->player.x = new_x;
		if (is_walkable(data, data->player.x, new_y))
			data->player.y = new_y;
	}

	if (data->input[KEY_RIGHT])
	{
		data->player.angle += ROT_SPEED;
		if (data->player.angle >= 2 * PI) // Toujours compris dans {0, 2pi}
			data->player.angle -= 2 * PI; 
	}

	if (data->input[KEY_LEFT])
	{
		data->player.angle -= ROT_SPEED;
		if (data->player.angle < 0)
			data->player.angle += 2 * PI; 
	}
	return (0);
}

int main_loop(void *args)
{
	t_data *data;
	
	data = (t_data *)args;
	update_events(data);
	redraw(data);
	return (0);
}