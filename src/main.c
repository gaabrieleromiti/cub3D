/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:36:26 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/24 16:58:31 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


int	main(int argc, char **argv)
{
	t_config	*config;

	config = (t_config *)malloc(sizeof(t_config));
	if (!config)
	{
		ft_putstr_fd("Error\nMemory allocation failed for config\n", 2);
		exit(1);
	}
	init(argc, argv, config);

	printf("x: %d\ny: %d\ndir: %c\n", config->player->x, config->player->y,config->player->dir);
	// exit(1);


	setup_hooks(config);

	// free_config(config, NULL);

	// mlx_key_hook(config->mlx->win, check_key, config);
	// mlx_loop(config->mlx->mlx);

	// int	i = -1;
	// while (++i < (int)config->map->height)
	// {
	// 	int	j = -1;
	// 	while (config->map->map[i][++j])
	// 		printf("%-2c", config->map->map[i][j]);
	// 	printf("\n");
	// }
	// printf("height: %zu\n", config->map->height);

	return (0);
}