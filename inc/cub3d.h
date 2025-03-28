/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 12:37:20 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/27 18:06:56 by rkhakimu         ###   ########.fr       */
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

# define WIDTH 1000
# define HEIGHT 500
# define PI 3.14159265358979323846264338327950288

typedef struct s_rgb
{
	int		r;
	int		g;
	int		b;
}	t_rgb;

typedef struct s_player
{
    double x_pos;
    double y_pos;
    double x_dir;
    double y_dir;
    double x_plane;
    double y_plane;
	char orientation;
} t_player;

typedef struct s_raycast
{
	double x_cam;
	double x_raydir;
	double y_raydir;
	int		x_map;
	int		y_map;
	double x_side_dist;
	double y_side_dist;
	double x_delt_dist;
	double y_delt_dist;
	double wall_dist;
	double perp_dist;
	int x_step;
	int y_step;
	bool collision;
	int side;
	char dir;
	char texture_type;
	int wall_height;
} t_raycast;


typedef struct s_keys {
    bool w;
    bool a;
    bool s;
    bool d;
    bool left;
    bool right;
} t_keys;

typedef struct	s_texture
{
	char			*north;
	char			*south;
	char			*east;
	char			*west;
	mlx_texture_t	*tex_north;
	mlx_texture_t	*tex_south;
	mlx_texture_t	*tex_east;
	mlx_texture_t	*tex_west;
	mlx_texture_t	*vignette;
	mlx_image_t		*vigne;
}	t_texture;


typedef struct	s_game
{
	char		**map;
	int			map_width;
	int			map_height;
	int			width;
	int			height;
	int			map_offset_x;
	int			map_offset_y;
	int			scale;
	t_player	player;
	t_texture	textures;
	int			floor_rgb;
	int			ceiling_rgb;
	mlx_t		*mlx;
    mlx_image_t	*img;
	t_keys		keys;
	int			fd;
}	t_game;


/*DDA*/
void calc_ray_dir(t_raycast *r, int i, t_game* game);
void calc_delt_dist(t_raycast *r, int i, t_game* game);
void get_step_dir(t_raycast *r, int i, t_game* game);
void dda(t_raycast *r, t_game* game);
void calc_perpendicular_dist(t_raycast *r);

/*Player's movement*/
void key_hook(mlx_key_data_t keydata, void* param);
void player_hook(void* param);
void rotate(t_game* game, double rot_rad);
int is_valid_pos(t_game* game, double new_x, double new_y);

/* Minimap*/
void draw_square(t_game *game, int x, int y, int size, uint32_t color);
void draw_map(t_game* game);
void draw_player(t_game *game, int x, int y, int size, uint32_t color);

/* Rendering*/
int 			render(t_game *game);
int				calculate_wall_height(t_game *game, t_raycast *raycast);
void			calculate_wall_position(t_game *game, t_raycast *raycast, int *draw_start, int *draw_end);
void			draw_wall_strip(t_game *game, int x, int draw_start, int draw_end, t_raycast *r);
void			draw_floor(t_game *game, int x, int *draw_end);
void			draw_ceiling(t_game *game, int x, int *draw_start);
uint32_t get_color(t_game * game, t_raycast *r, int total_y, int draw_start);

/*Errors*/
void			error_exit(char *msg, t_game *game);
void			free_game(t_game *game);

/* Freeing */
void			free_map(t_game *game);
void			free_texture_pair(char **path, mlx_texture_t **texture);
void			free_textures(t_game *game);
void			free_mlx(t_game *game);
void			free_game(t_game *game);


/* Parsing functions */
void			parse_cub_file(t_game *game, char *filename);
char			*parse_config(t_game *game, int fd);
void			parse_map_start(t_game *game, int fd, char *first_map_line);
char			*skip_empty_lines(t_game *game, int fd, char *first_map_line);
int				validate_file_ext(char *filename);
int				validate_file_access(char *filename);
int				validate_tex_ext(char *filename, t_game *game);
int				is_config_element(char *line);
void			init_game(t_game *game);
void			parse_texture(t_texture *textures, char *line, t_game *game);
char			*extract_texture_path(char *line, t_game *game);
int				assign_north_south_texture(t_texture *textures, char *line, char *path, t_game *game);
int 			assign_east_west_texture(t_texture *textures, char *line, char *path, t_game *game);
void			parse_texture(t_texture *textures, char *line, t_game *game);
int				parse_rgb_component(char **ptr, char delimiter, t_game *game, char *line);
void			parse_color(int *color, char *line, t_game *game);
void			validate_config(t_game *game);
int				is_newline(char *line);

/* Loading textures */
mlx_texture_t	*load_texture_file(char *path, t_game *game);
void			load_textures(t_game *game);

/* MAP */
void			read_map(t_game *game, int fd);
void			validate_map(t_game *game);
char			**ft_realloc_2d(char **old, int new_size);
void			check_row(char *row, int y, t_game *game, int *player_found);
void			flood_fill(t_game *game, int x, int y, char **map);

#endif