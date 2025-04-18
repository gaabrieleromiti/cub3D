/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:35:48 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/18 15:58:45 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>

// # include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_map
{
	char	**map;
	
	size_t	width;
	size_t	height;
}	t_map;

typedef struct t_textures
{
	char	*NO_texture;
	char	*SO_texture;
	char	*WE_texture;
	char	*EA_texture;

	char	*F_colour;
	char	*C_colour;
}	t_textures;

typedef struct s_config
{
	char		*filename;
	int			fd;

	t_map		*map;
	int			parsing_map;

	t_textures	*textures;
}	t_config;

// input.c
int		check_extension(char *filename);
int		check_args(int argc, char **arg);
int		init(int argc, char **argv, t_config *config);

// parser.c
int		is_map_line(char *line);
int		parse_line(t_config *config, char *line);
int		parse_map_line(t_config *config, char *line);
int		parse_texture_or_colour_line(t_config *config, char *line);
int		parse(t_config *config);




#endif