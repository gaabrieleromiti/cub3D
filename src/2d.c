/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:59:17 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/28 11:08:39 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_tile_size(t_config *config)
{
	int	max_width;
	int	max_height;

	max_width = WIN_WIDTH / config->map->width;
	max_height = WIN_HEIGHT / config->map->height;
	if (max_width < max_height)
		config->mlx->tile_size = max_width;
	else
		config->mlx->tile_size = max_height;
}

void	my_pixel_put(t_config *config, int x, int y, int colour)
{
	char	*dst;

	dst = config->mlx->img->addr + (y * config->mlx->img->line_length + \
			x * (config->mlx->img->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

void	draw_tile(t_config *config, int x, int y, int colour)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;

	i = -1;
	start_x = x * config->mlx->tile_size;
	start_y = y * config->mlx->tile_size;
	while (++i < config->mlx->tile_size)
	{
		j = -1;
		while (++j < config->mlx->tile_size)
			my_pixel_put(config, start_x + j, start_y + i, colour);
	}
}

void	draw_player(t_config *config)
{
	int	i;
	int	j;
	int	start_x;
	int	start_y;
	int	tile_size;
	int	player_size;

	i = -1;
	tile_size = config->mlx->tile_size;
	player_size = tile_size / 3;
	start_x = (config->player->x * tile_size) + (tile_size / 2) - (player_size / 2);
	start_y = (config->player->y * tile_size) + (tile_size / 2) - (player_size / 2);
	while (++i < player_size)
	{
		j = -1;
		while (++j < player_size)
			my_pixel_put(config, start_x + j, start_y + i, PLAYER_COLOUR);
	}
}

void	draw_map(t_config *config)
{
	int		x;
	int		y;
	char	c;

	y = -1;
	get_tile_size(config);
	while (++y < (int)config->map->height)
	{
		x = -1;
		while (++x < (int)ft_strlen(config->map->map[y]))
		{
			c = config->map->map[y][x];
			if (c == '1')
				draw_tile(config, x, y, WALL_COLOUR);
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
				draw_tile(config, x, y, FLOOR_COLOUR);
			if (c == ' ')
				draw_tile(config, x, y, EMPTY_SPACE_COLOUR);
			// if (c == 'p')
			// 	draw_player(config);
		}
	}
}

int	move(int keycode, t_config *config)
{
	if (!check_key(keycode, config))
		return (0);
	render_2d(config);
	return (1);
}

void	render_2d(t_config *config)
{
	if (config->mlx->img->img)
		mlx_destroy_image(config->mlx->mlx, config->mlx->img->img);
	config->mlx->img->img = mlx_new_image(config->mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	config->mlx->img->addr = mlx_get_data_addr(config->mlx->img->img, \
		&(config->mlx->img->bits_per_pixel), &(config->mlx->img->line_length), \
		&(config->mlx->img->endian));
	if (!config->mlx->img->addr)
		free_config(config, "Error\nFailed to get image address");
	draw_map(config);
	draw_player(config);
	mlx_put_image_to_window(config->mlx->mlx, config->mlx->win, \
		config->mlx->img->img, 0, 0);

}