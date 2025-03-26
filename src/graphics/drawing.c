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

	if (raycast->perp_dist < 0.1)
		wall_height = game->height;
	else
		wall_height = (int)(game->height / raycast->perp_dist);
	return (wall_height);	
}

void	calculate_wall_position(t_game *game, t_raycast *raycast, int *draw_start, int *draw_end)
{
	raycast->wall_height = calculate_wall_height(game, raycast);
	
	*draw_start = (game->height / 2) - (raycast->wall_height / 2);
	*draw_end = (game->height / 2) + (raycast->wall_height / 2);
	// printf("draw_start: %d\n", *draw_start);
	// printf("draw_end: %d\n", *draw_end);
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end > game->height)
		*draw_end = game->height;
}

void	draw_floor(t_game *game, int x, int *draw_end)
{
	int	y;
	
	y = *draw_end;
	while (y < game->height)
	{
		mlx_put_pixel(game->img, x, y, game->floor_rgb);
		y++;
	}
}

void	draw_ceiling(t_game *game, int x, int *draw_start)
{
	int	y;

	y = 0;
	while (y < *draw_start)
	{
		mlx_put_pixel(game->img, x, y, game->ceiling_rgb);
		y++;
	}
}

void	draw_wall_strip(t_game *game, int x, int draw_start, int draw_end, t_raycast *r)
{
	int	y;

	draw_ceiling(game, x, &draw_start);
	y = draw_start;
	while (y < draw_end)
	{
		mlx_put_pixel(game->img, x, y, get_color(game, r, y, draw_start));
		y++;
	}
	draw_floor(game, x, &draw_end);
}
