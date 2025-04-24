/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 14:59:17 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/24 18:12:57 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	my_pixel_put(t_config *config, int x, int y, int colour)
{
	char	*dst;

	dst = config->mlx->img.addr + (y * config->mlx->img.line_length + \
			x * (config->mlx->img.bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

void	draw_tile(t_config *config, int x, int y, int colour)
{
	int	i;
	int	j;

	i = -1;
	while (++i < TILE_SIZE)
	{
		j = -1;
		while (++j < TILE_SIZE)
			my_pixel_put(config, x + j, y + i, colour);
	}
}

// void	draw_player()

void	draw_map(t_config *config)
{
	int		x;
	int		y;
	char	c;

	y = -1;
	while (++y < config->map->height)
	{
		x = -1;
		while (++x < ft_strlen(config->map->map[y]) - 1)
		{
			c = config->map->map[y][x];
			if (c == '1')
				draw_tile(config, x, y, WALL_COLOUR);
			if (c == '0')
				draw_tile(config, x, y, FLOOR_COLOUR);
			if (c == ' ')
				draw_tile(config, x, y, EMPTY_SPACE_COLOUR);
			if (c == 'p')
				draw_player(config, x, y, PLAYER_COLOUR);
		}
	}
}
