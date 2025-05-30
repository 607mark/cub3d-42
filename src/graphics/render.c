/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:15:08 by mshabano          #+#    #+#             */
/*   Updated: 2025/04/07 10:55:18 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_hook(void *param)
{
	t_game		*game;
	t_raycast	r;
	int			i;

	game = (t_game *)param;
	ft_memset(game->img->pixels, 0, game->img->width * game->img->height
		* sizeof(int32_t));
	ft_memset(game->minimap->pixels, 0, game->minimap->width
		* game->minimap->height * sizeof(int32_t));
	i = -1;
	while (++i < game->width)
	{
		ft_memset(&r, 0, sizeof(t_raycast));
		calc_ray_dir(&r, i, game);
		calc_delt_dist(&r);
		set_step_dir(&r, game);
		dda(&r, game);
		calc_perpendicular_dist(&r);
		calculate_wall_position(game, &r);
		draw_wall_strip(game, i, &r);
	}
	draw_map(game);
}

int	set_mlx(t_game *game)
{
	game->mlx = mlx_init(game->width, game->height, "cub3D", 0);
	if (game->mlx == NULL)
		return (1);
	game->img = mlx_new_image(game->mlx, game->width, game->height);
	game->minimap = mlx_new_image(game->mlx, 410, 410);
	if (game->img == NULL || game->minimap == NULL)
		return (1);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
		return (1);
	if (mlx_image_to_window(game->mlx, game->minimap,
			game->map_offset_x, game->map_offset_y) == -1)
		return (1);
	game->minimap->enabled = (!game->minimap->enabled);
	return (0);
}

void	set_player(t_game *game)
{
	game->player.x_pos += 0.5;
	game->player.y_pos += 0.5;
	game->player.x_dir = 0;
	game->player.y_dir = -1;
	game->player.x_plane = 0.7;
	if (game->player.orientation == 'E')
		rotate(game, PI / 2);
	else if (game->player.orientation == 'S')
		rotate(game, PI);
	else if (game->player.orientation == 'W')
		rotate(game, -PI / 2);
}

int	init(t_game *game)
{
	set_player(game);
	game->scale = 400 / game->map_height;
	if (game->map_width > game->map_height)
		game->scale = 400 / game->map_width;
	game->width = 1920;
	game->height = 1080;
	game->map_offset_x = game->width - game->map_width * game->scale
		- game->scale - 10;
	game->map_offset_y = game->scale + 10;
	ft_memset(&game->keys, 0, sizeof(t_keys));
	if (set_mlx(game) == 1)
		return (1);
	return (0);
}

int	render(t_game *game)
{
	if (init(game) == 1)
		return (1);
	if (mlx_loop_hook(game->mlx, player_hook, game) == false
		|| mlx_loop_hook(game->mlx, draw_hook, game) == false)
		return (1);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
	return (0);
}
