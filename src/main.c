/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:36:26 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/18 16:49:52 by gromiti          ###   ########.fr       */
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
	puts("config malloc");
	if (init(argc, argv, config))
	{
		free(config);
		return (1);
	}
	printf("map->height: %zu\n", config->map->height);
	printf("map->width: %zu\n", config->map->width);
	printf("%s\n", config->map->map[13]);
	for (int i = 0; i < (int)config->map->height; i++)
	{
		printf("i: %d\n", i);
		// printf("%s\n", config->map->map[i]);
	}
	int	i = -1;
	while (++i < (int)config->map->height)
	{
		// printf("i: %d\n", i);
		printf ("%s\n", config->map->map[i]);
	}


	

}