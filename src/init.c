/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:34:48 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/23 12:00:40 by gromiti          ###   ########.fr       */
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
int	check_args(int argc, char **argv)
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
** init_config - Initialize the configuration structure
** @config: The configuration structure to fill.
** @filename: The name of the file to open.
**
** Return: 0 if successful, 1 if an error occurred.
**
** This function initializes the configuration structure by opening the file
** and setting the contained fields to NULL. If the file cannot be opened, it prints
** an error message and returns 1. Otherwise, it returns 0.
** The function also sets the parsing_map field to 0.
*/
int	init_config(t_config *config, char *filename)
{
	config->filename = filename;
	config->fd = open(filename, O_RDONLY);
	if (config->fd < 0)
	{
		printf("Error\nFailed to open file: %s\n", filename);
		return (1);
	}
	config->map = NULL;
	config->textures = NULL;
	config->mlx = NULL;
	config->player = NULL;
	config->parsing_map = 0;
	return (0);
}

/*
** init_map - Initialize the map structure
** @config: The configuration structure to fill.
**
** Return: 0 if successful, 1 if an error occurred.
**
** This function allocates memory for the map structure and initializes its
** fields. If memory allocation fails, it prints an error message and returns 1.
** Otherwise, it returns 0.
*/
int	init_map(t_config *config)
{
	config->map = malloc(sizeof(t_map));
	config->map->map = NULL;
	config->map->height = 0;
	config->map->width = 0;
	if (!config->map)
	{
		printf("Error\nMemory allocation failed\n");
		return (1);
	}
	return (0);
}

/*
** init_textures - Initialize the textures structure
** @config: The configuration structure to fill.
**
** Return: 0 if successful, 1 if an error occurred.
**
** This function allocates memory for the textures structure and initializes
** its fields. If memory allocation fails, it prints an error message and
** returns 1. Otherwise, it returns 0.
*/
int	init_textures(t_config *config)
{
	config->textures = malloc(sizeof(t_textures));
	if (!config->textures)
	{
		printf("Error\nMemory allocation failed for textures\n");
		return (1);
	}
	config->textures->NO_texture = NULL;
	config->textures->SO_texture = NULL;
	config->textures->WE_texture = NULL;
	config->textures->EA_texture = NULL;
	config->textures->F_colour = NULL;
	config->textures->C_colour = NULL;
	return (0);
}

int	init_player(t_config *config)
{
	config->player = malloc(sizeof(t_player));
	if (!config->player)
	{
		printf("Error\nMemory allocation failed for player\n");
		return (1);
	}
	config->player->x = 0;
	config->player->y = 0;
	config->player->dir = 0;
	return (0);
}

/*
** init_window - Initialize the window using mlx
** @mlx: The mlx structure to fill.
**
** Return: 0 if successful, 1 if an error occurred.
**
** This function initializes the mlx library and creates a new window with
** the specified dimensions and title. If any of these steps fail, it prints
** an error message and returns 1. Otherwise, it returns 0.
*/
int init_window(t_config *config)
{
	config->mlx = malloc(sizeof(t_mlx));
	if (!config->mlx)
	{
		printf("Error\nMemory allocation failed for mlx\n");
		return (1);
	}
	config->mlx->win = NULL;
	config->mlx->mlx = NULL;
	config->mlx->mlx = mlx_init();
	if (!config->mlx->mlx)
	{
		printf("Error\nFailed to initialize mlx\n");
		return (1);
	}
	config->mlx->win = mlx_new_window(config->mlx->mlx, config->map->width * 32, config->map->height * 32, "Cub3D");
	if (!config->mlx->win)
	{
		printf("Error\nFailed to create window\n");
		return (1);
	}
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
int	init(int argc, char **argv, t_config *config)
{
	if (check_args(argc, argv))
		return (1);
	if (init_config(config, argv[1]))
		return (1);
	if (init_map(config))
		return (1);
	if (init_textures(config))
		return (1);
	if (parse(config))
		return (1);
	if (init_window(config))
		return (1);
	close(config->fd);
	return (0);
}
