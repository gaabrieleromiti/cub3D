/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:53:44 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/24 12:40:00 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
** set_start_pos - Set the starting position of the player
** @config: The configuration structure to fill.
**
** This function iterates through the map and finds the starting position of
** the player. It sets the player's x and y coordinates and direction based on
** the character found in the map. If multiple starting positions are found or
** no starting position is found, it prints an error message and frees the
** configuration structure.
*/
void	set_start_pos(t_config *config)
{
	int		i;
	int		j;
	int		start;
	char	c;

	i = -1;
	start = 0;
	while (++i < (int)config->map->height)
	{
		j = -1;
		while (config->map->map[i][++j])
		{
			c = config->map->map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				config->player->x = j;
				config->player->y = i;
				config->player->dir = c;
				if (++start > 1)
					free_config(config, "Error\nMultiple starting positions found\n");
			}
		}
	}
	if (start == 0)
		free_config(config, "Error\nNo starting position found\n");
}

void	check_wall(t_config *config)
{
	int	r;
	int	c;

	r = -1;
	while (++r < (int)config->map->height)
	{
		c = -1;
		while (++c < (int)ft_strlen(config->map->map[r]))
		{
			if (config->map->map[r][c] == '0')
			{
				if (r == 0 || r == (int)config->map->height - 1)
					free_config(config, "Error\nMap is not closed\n");
				if (c == 0 || c == (int)ft_strlen(config->map->map[r]) - 1)
					free_config(config, "Error\nMap is not closed\n");
				if (config->map->map[r][c - 1] == ' ' || config->map->map[r][c + 1] == ' ' ||
					config->map->map[r - 1][c] == ' ' || config->map->map[r + 1][c] == ' ')
					free_config(config, "Error\nMap is not closed\n");
			}
		}
	}
}

int	check_key(int keycode, t_config *config)
{
	if (keycode == KEY_ESC)
		free_config(config, NULL);
	if (keycode == KEY_W)
		config->player->x += 1;
	else if (keycode == KEY_A)
		config->player->y -= 1;
	else if (keycode == KEY_S)
		config->player->x -= 1;
	else if (keycode == KEY_D)
		config->player->y += 1;
	else if (keycode == KEY_LEFT)
		config->player->dir -= 1;
	else if (keycode == KEY_RIGHT)
		config->player->dir += 1;
	return (1);
}
