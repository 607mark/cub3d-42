/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:39:03 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/24 13:15:03 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	calculate_wall_height(t_game *game, t_raycast *raycast)
{
	int	wall_height;

	if (raycast->perp_dist < 0.01)
		wall_height = game->height * 20;
	else
		wall_height = (int)(game->height / raycast->perp_dist);
	return (wall_height);
}

void	calculate_wall_position(t_game *game, t_raycast *raycast)
{
	raycast->wall_height = calculate_wall_height(game, raycast);
	raycast->draw_start = (game->height / 2) - (raycast->wall_height / 2);
	raycast->draw_end = (game->height / 2) + (raycast->wall_height / 2);
	if (raycast->draw_end > game->height)
		raycast->draw_end = game->height;
}

void	draw_floor(t_game *game, int x, t_raycast *raycast)
{
	int	y;

	y = raycast->draw_end;
	while (y < game->height)
	{
		if (y < 0)
		{
			y++;
			continue ;
		}
		mlx_put_pixel(game->img, x, y, game->floor_rgb);
		y++;
	}
}

void	draw_ceiling(t_game *game, int x, t_raycast *raycast)
{
	int	y;

	y = 0;
	while (y < raycast->draw_start)
	{
		if (y < 0)
		{
			y++;
			continue ;
		}
		mlx_put_pixel(game->img, x, y, game->ceiling_rgb);
		y++;
	}
}

void	draw_wall_strip(t_game *game, int x, t_raycast *r)
{
	int	y;

	draw_ceiling(game, x, r);
	y = r->draw_start;
	while (y < r->draw_end)
	{
		if (y < 0)
		{
			y++;
			continue ;
		}
		mlx_put_pixel(game->img, x, y, get_color(game, r, y));
		y++;
	}
	draw_floor(game, x, r);
}
