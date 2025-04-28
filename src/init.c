/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:34:48 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/28 10:17:27 by gromiti          ###   ########.fr       */
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
		free_config(NULL, "Error\nInvalid file extension. Expected .cub\n");
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
void	check_args(int argc, char **argv)
{
	if (argc != 2)
		free_config(NULL, "Error\nInvalid number of arguments\n");
	check_extension(argv[1]);
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
void	init_config(t_config *config, char *filename)
{
	config->filename = filename;
	config->fd = open(filename, O_RDONLY);
	if (config->fd < 0)
		free_config(config, "Error\nFailed to open file\n");
	config->map = NULL;
	config->textures = NULL;
	config->mlx = NULL;
	config->player = NULL;
	config->parsing_map = 0;
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
void	init_map(t_config *config)
{
	config->map = malloc(sizeof(t_map));
	if (!config->map)
		free_config(config, "Error\nMemory allocation failed for map\n");
	config->map->map = NULL;
	config->map->height = 0;
	config->map->width = 0;
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
void	init_textures(t_config *config)
{
	config->textures = malloc(sizeof(t_textures));
	if (!config->textures)
		free_config(config, "Error\nMemory allocation failed for textures\n");
	config->textures->NO_texture = NULL;
	config->textures->SO_texture = NULL;
	config->textures->WE_texture = NULL;
	config->textures->EA_texture = NULL;
	config->textures->F_colour = NULL;
	config->textures->C_colour = NULL;
}

/*
** init_player - Initialize the player structure
** @config: The configuration structure to fill.
**
** Return: 0 if successful, 1 if an error occurred.
**
** This function allocates memory for the player structure and initializes
** its fields. If memory allocation fails, it prints an error message and
** returns 1. Otherwise, it returns 0.
*/
void	init_player(t_config *config)
{
	config->player = malloc(sizeof(t_player));
	if (!config->player)
		free_config(config, "Error\nMemory allocation failed for player\n");
	config->player->x = 0;
	config->player->y = 0;
	config->player->spawn_direction = 0;
}

/*
** init_mlx - Initialize the mlx structure
** @mlx: The mlx structure to fill.
**
** Return: 0 if successful, 1 if an error occurred.
**
** This function initializes the mlx library and creates a new window with
** the specified dimensions and title. If any of these steps fail, it prints
** an error message and returns 1. Otherwise, it returns 0.
*/
void	init_mlx(t_config *config)
{
	if (!config)
		return;
	config->mlx = malloc(sizeof(t_mlx));
	if (!config->mlx)
		free_config(config, "Failed to allocate memory for MLX");
	config->mlx->mlx = mlx_init();
	if (!config->mlx->mlx)
		free_config(config, "Failed to initialize MLX");
	config->mlx->win = mlx_new_window(config->mlx->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (!config->mlx->win)
		free_config(config, "Failed to create window");
	config->mlx->img = malloc(sizeof(t_img));
	if (!config->mlx->img)
		free_config(config, "Failed to allocate memory for image");
	config->mlx->img->img = mlx_new_image(config->mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!config->mlx->img->img)
		free_config(config, "Failed to create image");
	config->mlx->img->addr = mlx_get_data_addr(config->mlx->img->img, &(config->mlx->img->bits_per_pixel), &(config->mlx->img->line_length), &(config->mlx->img->endian));
	if (!config->mlx->img->addr)
		free_config(config, "Failed to get image address");
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
void	init(int argc, char **argv, t_config *config)
{
	check_args(argc, argv);
	init_config(config, argv[1]);
	init_map(config);
	init_player(config);
	init_textures(config);
	parse(config);
	set_start_pos(config);
	check_wall(config);
	init_mlx(config);
	close(config->fd);
}
