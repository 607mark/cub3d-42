/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshabano <mshabano@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:06:00 by mshabano          #+#    #+#             */
/*   Updated: 2025/03/31 22:08:50 by mshabano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// rotation matrix for wikipedia
void	rotate_vector(double *x, double *y, double rad)
{
	double	x_old;
	double	cos_angle;
	double	sin_angle;

	x_old = *x;
	cos_angle = cos(rad);
	sin_angle = sin(rad);
	*x = x_old * cos_angle - *y * sin_angle;
	*y = x_old * sin_angle + *y * cos_angle;
}

//rotates both player's dir and plane dir(perpendicular to player)
void	rotate(t_game *game, double rot_rad)
{
	rotate_vector(&game->player.x_dir, &game->player.y_dir, rot_rad);
	rotate_vector(&game->player.x_plane, &game->player.y_plane, rot_rad);
}

void	move(t_game *game, double x_dir, double y_dir, double speed)
{
	double	x_new;
	double	y_new;

	x_new = game->player.x_pos + x_dir * speed * 2;
	y_new = game->player.y_pos + y_dir * speed * 2;
	if (is_valid_pos(game, x_new, game->player.y_pos))
		game->player.x_pos = game->player.x_pos + x_dir * speed;
	if (is_valid_pos(game, game->player.x_pos, y_new))
		game->player.y_pos = game->player.y_pos + y_dir * speed;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keydata.key == MLX_KEY_W)
		game->keys.w = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_S)
		game->keys.s = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_A)
		game->keys.a = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_D)
		game->keys.d = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_LEFT)
		game->keys.left = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_RIGHT)
		game->keys.right = (keydata.action != MLX_RELEASE);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_M && keydata.action == MLX_PRESS)
		game->minimap->enabled = (!game->minimap->enabled);
}

void	player_hook(void *param)
{
	t_game	*game;
	double	move_speed;
	double	rot_speed;

	game = (t_game *)param;
	move_speed = 0.3;
	rot_speed = 0.1;
	if (game->keys.w)
		move(game, game->player.x_dir, game->player.y_dir, move_speed);
	if (game->keys.s)
		move(game, -game->player.x_dir, -game->player.y_dir, move_speed);
	if (game->keys.a)
		move(game, game->player.y_dir, -game->player.x_dir, move_speed);
	if (game->keys.d)
		move(game, -game->player.y_dir, game->player.x_dir, move_speed);
	if (game->keys.left)
		rotate(game, -rot_speed);
	if (game->keys.right)
		rotate(game, rot_speed);
}
