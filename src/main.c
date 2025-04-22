/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:36:26 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/22 19:56:40 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_config	*config;

	config = (t_config *)malloc(sizeof(t_config));
	if (!config)
	{
		printf("Error\nMemory allocation failed\n");
		return (1);
	}
	if (init(argc, argv, config))
	{
		free(config);
		// must free everything in config
		return (1);
	}
	int	i = -1;
	while (++i < (int)config->map->height)
	{
		int	j = -1;
		while (config->map->map[i][++j])
		{
			// Print each character with a fixed width of 2
			printf("%-2c", config->map->map[i][j]);
			// if (j == 9)
			// 	printf("%c", config->map->map[i][j]);
		}
		printf("\n");
	}
	printf("height: %zu\n", config->map->height);
	// printf("%s\n", config->map->map[0]);
	// while (++i < (int)config->map->width)
	// 	printf("i: %d, c: %c\n", i, config->map->map[0][i]);

	while(++i < (int)config->map->height)
		free(config->map->map[i]);
	free(config->map->map);
	free(config->map);
	// free(config->textures->NO_texture);
	// free(config->textures->SO_texture);
	// free(config->textures->WE_texture);
	// free(config->textures->EA_texture);
	// free(config->textures->F_colour);
	// free(config->textures->C_colour);
	free(config->textures);
	free(config);
	return (0);
}