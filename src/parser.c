/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:33:45 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/17 17:20:22 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	assign_path(char *line)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		// Assign North texture path
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		// Assign South texture path
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		// Assign West texture path
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		// Assign East texture path
	}
	else if (ft_strncmp(line, "F", 1) == 0)
	{
		// Assign Floor color
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		// Assign Ceiling color
	}
	else
	{
		printf("Error\nInvalid line format\n");
		return (1);
	}
}

int	parse(t_config *config)
{
	char	*line;

	
}
