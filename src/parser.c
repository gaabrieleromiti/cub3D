/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:33:45 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/21 16:41:59 by gromiti          ###   ########.fr       */
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
char	*replace_tabs(char* line)
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
	new_line = (char *)malloc(sizeof(char) * (i + spaces + 1));
	if (!new_line)
	{
		printf("Error\nMemory allocation failed\n");
		return (NULL);
	}
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
		else
			new_line[++j] = line[i];
	}
	new_line[++j] = '\0';
	return (new_line);
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
int	parse_map_line(t_config *config, char *line)
{
	if (!config->parsing_map)
	{
		config->map->map = (char **)malloc(sizeof(char *) * 1);
		if (!config->map->map)
		{
			printf("Error\nMemory allocation failed\n");
			return (1);
		}
		config->parsing_map = 1;
		config->map->height = 1;
	}
	config->map->map = ft_realloc(config->map->map, sizeof(char *) * (config->map->height));
	if (!config->map->map)
	{
		printf("Error\nMemory allocation failed\n");
		return (1);
	}
	config->map->map[config->map->height - 1] = replace_tabs(line);
	if (!config->map->map[config->map->height - 1])
	{
		printf("Error\nMemory allocation failed\n");
		return (1);
	}
	config->map->height++;
	if (config->map->width < ft_strlen(line))
		config->map->width = ft_strlen(line);
	return (0);
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
int	parse_texture_or_colour_line(t_config *config, char *line)
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
		return (1);
	if (!config->textures->NO_texture || !config->textures->SO_texture || \
		!config->textures->WE_texture || !config->textures->EA_texture || \
		!config->textures->F_colour || !config->textures->C_colour)
	{
		printf("Error\nMemory allocation failed for textures or colours\n");
		return (1);
	}
	return (0);
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
int	parse_line(t_config *config, char *line)
{
	if (is_map_line(line))
	{
		parse_map_line(config, line);
	}
	else if (!config->parsing_map)
	{
		if (parse_texture_or_colour_line(config, line))
		{
			printf("Error\nInvalid texture or colour line: %s\n", line);
			return (1);
		}
	}
	else
	{
		printf("Error\nNon-map line after map started: %s\n", line);
		return (1);
	}
	return (0);
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
int	parse(t_config *config)
{
	char	*line;

	while ((line = get_next_line(config->fd)) != NULL)
	{
		if (line[0] == '\n' || line[0] == '\0')
		{
			if (config->parsing_map == 1)
			{
				printf("Error\nEmpty line in map\n");
				free(line);
				return (1);
			}
			free(line);
			continue;
		}
		if (parse_line(config, line))
		{
			free(line);
			return (1);
		}
		free(line);
	}
	config->map->height--;
	config->map->map[config->map->height] = NULL;
	return (0);
}
