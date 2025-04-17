/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:34:48 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/17 17:19:39 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
** check_extension - Check if the file has a .cub extension
** @filename: The name of the file to check.
**
** Return: 0 if the extension is valid, 1 if it is not.
**
** This function checks if the last four characters of the filename are ".cub".
** If not, it prints an error message and returns 1. Otherwise, it returns 0.
*/
int	check_extension(char *filename)
{
	if (ft_strncmp(filename + ft_strlen(filename) - 4, ".cub", 4) != 0)
	{
		printf("Error\nInvalid file extension. Expected .cub\n");
		return (1);
	}
	return (0);
}
/*
** check_args - Check the number of arguments and the file extension
** @argc: The number of arguments.
** @argv: The array of arguments.
** @config: The configuration structure to fill.
**
** Return: 0 if the arguments are valid, 1 if they are not.
**
** This function checks if the number of arguments is correct (2) and if the
** file has a valid extension. If not, it prints an error message and returns 1.
** Otherwise, it returns 0.
*/
int	check_args(int argc, char **argv, t_config *config)
{
	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments\n");
		return (1);
	}
	if (check_extension(argv[1]))
		return (1);
	return (0);
}

/*
** init - Initialize the configuration structure
** @argc: The number of arguments.
** @argv: The array of arguments.
**
** Return: 0 if successful, 1 if an error occurred.
**
** This function initializes the configuration structure by checking the
** arguments, opening the file, and allocating memory for the map and textures.
** If any of these steps fail, it prints an error message and returns 1.
** Otherwise, it returns 0.
*/
int	init(int argc, char **argv)
{
	t_config	*config;
	
	if (check_args(argc, argv, config))
		return (1);
	config = malloc(sizeof(t_config));
	if (!config)
	{
		printf("Error\nMemory allocation failed\n");
		return (1);
	}
	config->filename = argv[1];
	config->fd = open(config->filename, O_RDONLY);
	if (config->fd < 0)
	{
		printf("Error\nFailed to open file: %s\n", config->filename);
		return (1);
	}
	config->map = malloc(sizeof(t_map));
	if (!config->map)
	{
		printf("Error\nMemory allocation failed\n");
		return (1);
	}
	config->textures = malloc(sizeof(t_textures));
	if (!config->textures)
	{
		printf("Error\nMemory allocation failed\n");
		return (1);
	}
	if (parse(config))
		return (1);
	close(config->fd);
	return (0);
}
