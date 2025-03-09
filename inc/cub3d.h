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

typedef struct s_win
{
	mlx_t	*mlx;
	int	h;
	int	w;
}	t_win;



typedef struct	s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double 		plane_x;
    double		plane_y;
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
	int		**map;
	int			map_width;
	int			map_height;
	t_player	player;
	t_texture	textures;
	uint32_t			floor_rgb;
	uint32_t			ceiling_rgb;
	t_win		win;
	mlx_image_t *img;
}	t_game;


void	init_win(t_game *game);
#endif