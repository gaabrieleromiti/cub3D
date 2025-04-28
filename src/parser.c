/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:33:45 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/28 10:50:27 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
** is_map_line - Check if the line is a map line
** @line: The line to check.
**
** Return: 1 if the line is a map line, 0 if it is not.
**
** This function checks if the line contains only valid characters for a map line.
** Valid characters are '1', '0', ' ', '\t', 'N', 'S', 'E', and 'W'.
** If the line contains any other character, it returns 0. Otherwise, it returns 1.
*/
int	is_map_line(char *line)
{
	int	i;
	int	valid_char;

	i = -1;
	valid_char = 0;
	while (line[++i])
	{
		if (line[i] != '1' && line[i] != '0' && \
			line[i] != ' ' && line[i] != '\t' && \
			line[i] != 'N' && line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
		{
			if ((line[i] == '\n'|| line[i] == '\0') && valid_char == 1)
				continue;
			return (0);
		}
		else if (line[i] != ' ' && line[i] != '\t')
			valid_char = 1;
	}
	return (1);
}

/*
** replace_tabs - Replace tabs with spaces in a line
** @line: The line to replace tabs from.
**
** Return: A new line with tabs replaced by spaces.
**
** This function replaces each tab character in the line with a number of spaces
** equal to the tab width. It allocates memory for the new line and returns it.
** If memory allocation fails, it prints an error message and returns NULL.
** The new line is null-terminated.
*/
char	*replace_tabs(char *line)
{
	int		i;
	int		j;
	int		k;
	int		spaces;
	char	*new_line;

	i = -1;
	spaces = 0;
	while (line[++i])
	{
		if (line[i] == '\t')
			spaces += TAB_WIDTH - 1;
	}
	new_line = (char *)malloc(sizeof(char) * (i + spaces));
	if (!new_line)
		return (NULL);
	i = -1;
	j = -1;
	while (line[++i])
	{
		if (line[i] == '\t')
		{
			k = -1;
			while (++k < TAB_WIDTH)
				new_line[++j] = ' ';
		}
		else if (line[i] == '\n')
		{
			new_line[++j] = '\0';
			return (new_line);
		}
		else
			new_line[++j] = line[i];
	}
	new_line[++j] = '\0';
	return (new_line);
}

/*
** realloc_map - Reallocate memory for the map
** @map: The current map.
** @new_size: The new size of the map.
**
** Return: A new map with the new size.
**
** This function reallocates memory for the map to add a new line. It copies
** the old map to the new map and frees the old map. If memory allocation fails,
** it prints an error message and returns NULL. The new map is null-terminated.
*/
char	**realloc_map(char **map, size_t new_size)
{
	char	**new_map;
	size_t	i;

	i = -1;
	new_map = (char **)malloc(sizeof(char *) * new_size);
	if (!new_map)
		return (NULL);
	while (++i < new_size - 1)
		new_map[i] = map[i];
	free(map);
	return (new_map);
}

/*
** parse_map_line - Parse a map line
** @config: The configuration structure.
** @line: The line to parse.
**
** Return: 0 if successful, 1 if an error occurred.
**
** This function checks if the map has already started. If not, it allocates
** memory for the map and sets the height to 1. Then, it reallocates memory
** for the map to add the new line. It also duplicates the line and sets the
** height and width of the map. If any of these steps fail, it prints an error
** message and returns 1. Otherwise, it returns 0.
*/
void	parse_map_line(t_config *config, char *line)
{
	if (!config->parsing_map)
	{
		config->map->map = (char **)malloc(sizeof(char *) * 1);
		if (!config->map->map)
		{
			free(line);
			free_config(config, "Error\nMemory allocation failed for map\n");
		}
		config->parsing_map = 1;
		config->map->height = 1;
	}
	config->map->map = realloc_map(config->map->map, config->map->height);
	if (!config->map->map)
	{
		free(line);
		free_config(config, "Error\nMemory allocation failed for new_map\n");
	}
	config->map->map[config->map->height - 1] = replace_tabs(line);
	if (!config->map->map[config->map->height - 1])
	{
		free(line);
		free_config(config, "Error\nMemory allocation failed for new_line\n");
	}
	if (config->map->width < ft_strlen(config->map->map[config->map->height - 1]))
		config->map->width = ft_strlen(config->map->map[config->map->height - 1]);
	config->map->height++;
}

/*
** parse_texture_or_colour_line - Parse a texture or colour line
** @config: The configuration structure.
** @line: The line to parse.
**
** Return: 0 if successful, 1 if an error occurred.
**
** This function checks if the line is a texture or colour line. If it is, it
** duplicates the line and sets the corresponding texture or colour in the
** configuration structure. If any of these steps fail, it prints an error
** message and returns 1. Otherwise, it returns 0.
*/
void	parse_texture_or_colour_line(t_config *config, char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		config->textures->NO_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO", 2) == 0)
		config->textures->SO_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE", 2) == 0)
		config->textures->WE_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA", 2) == 0)
		config->textures->EA_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F", 1) == 0)
		config->textures->F_colour = ft_strdup(line + 2);
	else if (ft_strncmp(line, "C", 1) == 0)
		config->textures->C_colour = ft_strdup(line + 2);
	else
	{
		free(line);
		free_config(config, "Error\nInvalid texture or colour line\n");
	}
	if (!config->textures->NO_texture || !config->textures->SO_texture || \
		!config->textures->WE_texture || !config->textures->EA_texture || \
		!config->textures->F_colour || !config->textures->C_colour)
		{
			free(line);
			free_config(config, "Error\nMemory allocation failed for textures or colours\n");
		}
}

/*
** parse_line - Parse a line
** @config: The configuration structure.
** @line: The line to parse.
**
** Return: 0 if successful, 1 if an error occurred.
**
** This function checks if the line is a map line or a texture/colour line.
** If it is a map line, it calls the parse_map_line function. If it is a
** texture/colour line, it calls the parse_texture_line function. If any of
** these steps fail, it prints an error message and returns 1. Otherwise,
** it returns 0.
*/
void	parse_line(t_config *config, char *line)
{
	if (is_map_line(line))
		parse_map_line(config, line);
	else if (!config->parsing_map)
		parse_texture_or_colour_line(config, line);
	else
	{
		free(line);
		free_config(config, "Error\nInvalid line after map started\n");
	}
}

/*
** parse - Parse the configuration file
** @config: The configuration structure.
**
** Return: 0 if successful, 1 if an error occurred.
**
** This function reads the configuration file line by line and parses each line.
** It checks if the line is a map line or a texture/colour line and calls the
** appropriate parsing function. If any line is invalid, it prints an error
** message and returns 1. Otherwise, it returns 0.
*/
void	parse(t_config *config)
{
	char	*line;

	while ((line = get_next_line(config->fd)) != NULL)
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			if (config->parsing_map == 1)
			{
				free(line);
				free_config(config, "Error\nEmpty line in map\n");
			}
			free(line);
			continue;
		}
		parse_line(config, line);
		free(line);
	}
	config->map->height--;
}
