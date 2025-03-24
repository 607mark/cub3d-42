/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:39:03 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/24 11:33:49 by rkhakimu         ###   ########.fr       */
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

	int	wall_height;

	wall_height = calculate_wall_height(game, raycast);
	
	*draw_start = (game->height / 2) - (wall_height / 2);
	*draw_end = (game->height / 2) + (wall_height / 2);
	// printf("%d draw_start\n", *draw_start);
	// printf("%d draw_end\n", *draw_end);
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end > game->height)
		*draw_end = game->height;
}

void	draw_wall_strip(t_game *game, int x, int draw_start, int draw_end)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		// printf("x: %d\n", x);
		// printf("y: %d\n", y);
		mlx_put_pixel(game->img, x, y, 0x0000FFFF);
		y++;
	}
	y = draw_start;
	while (y < draw_end)
	{
		// printf("x: %d\n", x);
		// printf("y: %d\n", y);
		mlx_put_pixel(game->img, x, y, 0xFF0000FF);
		y++;
	}
	y = draw_end;
	while (y < game->height)
	{
		// printf("x: %d\n", x);
		// printf("y: %d\n", y);
		mlx_put_pixel(game->img, x, y, 0x00FF00FF);
		y++;
	}
}

