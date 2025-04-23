/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:35:48 by gromiti           #+#    #+#             */
/*   Updated: 2025/04/24 01:15:29 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

# define TAB_WIDTH 4
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_map
{
	char	**map;
	
	size_t	width;
	size_t	height;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_player
{
	int		x;
	int		y;
	char	dir;
}	t_player;

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

	t_player	*player;

	t_mlx		*mlx;

	t_textures	*textures;
}	t_config;

// free.c
void	free_map(t_map *map);
void	free_textures(t_textures *textures);
void	free_mlx(t_mlx *mlx);
void	free_config(t_config *config, char *error);

// init.c
int		check_extension(char *filename);
void	check_args(int argc, char **arg);
void	init_config(t_config *config, char *filename);
void	init_map(t_config *config);
void	init_textures(t_config *config);
void	init_window(t_config *config);
void	init_player(t_config *config);
void	init(int argc, char **argv, t_config *config);

// parser.c
int		is_map_line(char *line);
char	*replace_tabs(char* line);
char	**realloc_map(char **map, size_t new_size);
void	parse_map_line(t_config *config, char *line);
void	parse_texture_or_colour_line(t_config *config, char *line);
void	parse_line(t_config *config, char *line);
void	parse(t_config *config);

// window.c
void	set_start_pos(t_config *config);
void	check_wall(t_config *config);
int		check_key(int keycode, t_config *config);




#endif