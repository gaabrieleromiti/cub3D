/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 10:53:44 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/23 11:36:56 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_key(int keycode, t_config *config)
{
	if (keycode == KEY_ESC)
		free_config(config);
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
