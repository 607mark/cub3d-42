/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:37:20 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/06 09:44:16 by rkhakimu         ###   ########.fr       */
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
# include <errno.h>
# include <stdlib.h>

# define WIDTH 1000
# define HEIGHT 500

typedef struct s_player {
    double x_pos;
    double y_pos;
    double x_dir;
    double y_dir;
    double x_plane;
    double y_plane;
} t_player;


typedef struct s_keys {
    bool w_press;
    bool a_press;
    bool s_press;
    bool d_press;
    bool left_press;
    bool right_press;
} t_keys;

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
	int		**map;
	int			map_width;
	int			map_height;
	t_player	player;
	t_texture	textures;
	uint32_t			floor_rgb;
	uint32_t			ceiling_rgb;
	mlx_t* mlx;
    mlx_image_t* img;
	t_keys keys;
}	t_game;

#endif