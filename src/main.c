/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:36:26 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/21 16:07:43 by gromiti          ###   ########.fr       */
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
	// printf("%s\n", config->map->map[0]);
	// while (++i < (int)config->map->width)
	// 	printf("i: %d, c: %c\n", i, config->map->map[0][i]);
}