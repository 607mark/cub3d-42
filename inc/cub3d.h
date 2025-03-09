/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:37:20 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/10 00:26:10 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/Libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <stdlib.h>

typedef struct	s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	char		orientation;
}	t_player;

typedef struct	s_texture
{
	char		*north;
	char		*south;
	char		*east;
	char		*west;
	mlx_image_t	*img_north;
	mlx_image_t	*img_south;
	mlx_image_t	*img_east;
	mlx_image_t	*img_west;
}	t_texture;

typedef struct	s_game
{
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
	t_texture	textures;
	int			floor_rgb;
	int			ceiling_rgb;
	mlx_image_t	*img_ptr;
	mlx_t		*mlx_ptr;
}	t_game;



/*Errors*/
void	error_exit(char *msg);


#endif

/* Parsing functions */
void	error_exit(char *msg);
int		validate_file_ext(char *filename);
int		validate_file_access(char *filename);
int		is_config_element(char *line);
void	init_game(t_game *game);
void	parse_texture(t_texture *textures, char *line);
void	parse_color(int *color, char *line);

/* MAP */
void	read_map(t_game *game, int fd);
char	**ft_realloc_2d(char **old, int new_size);