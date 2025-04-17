/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:35:48 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/17 16:55:14 by gromiti          ###   ########.fr       */
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
	char	*filename;
	int		fd;
	char	**map;
	int		width;
	int		height;
}	t_map;

typedef struct t_textures
{
	char	*NO_texture;
	char	*SO_texture;
	char	*WE_texture;
	char	*EA_texture;
	char	*F_color;
	char	*C_color;
}	t_textures;

typedef struct s_config
{
	char		*filename;
	int			fd;
	t_map		*map;
	t_textures	*textures;
}	t_config;

#endif