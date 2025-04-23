/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:37:18 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/24 00:54:34 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_map(t_map *map)
{
	int	i;

	i = -1;
	while (++i < (int)map->height)
		free(map->map[i]);
	free(map->map);
	free(map);
}

void	free_textures(t_textures *textures)
{
	if (textures->NO_texture)
		free(textures->NO_texture);
	if (textures->SO_texture)
		free(textures->SO_texture);
	if (textures->WE_texture)
		free(textures->WE_texture);
	if (textures->EA_texture)
		free(textures->EA_texture);
	if (textures->F_colour)
		free(textures->F_colour);
	if (textures->C_colour)
		free(textures->C_colour);
	free(textures);
}

void	free_mlx(t_mlx *mlx)
{
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
		mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free(mlx);
}

void	free_config(t_config *config, char *error)
{
	if (config->fd >= 0)
		close(config->fd);
	if (config->map)
		free_map(config->map);
	if (config->textures)
		free_textures(config->textures);
	if (config->mlx)
		free_mlx(config->mlx);
	free(config->player);
	free(config);
	ft_putstr_fd(error, 2);
	exit(1);
}
