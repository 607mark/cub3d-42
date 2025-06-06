/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:47:34 by mshabano          #+#    #+#             */
/*   Updated: 2025/04/02 10:31:17 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_player(t_game *game, int x, int y, int size)
{
	t_draw	d;

	d.x_start = x;
	d.y_start = y;
	d.x_end = x + size;
	d.y_end = y + size;
	d.y_draw = d.y_start;
	while (d.y_draw <= d.y_end)
	{
		d.x_draw = d.x_start;
		while (d.x_draw <= d.x_end)
		{
			if (size == 12)
				put_pixel(game->minimap, d.x_draw, d.y_draw,
					0x000000FF);
			else
				put_pixel(game->minimap, d.x_draw, d.y_draw,
					0xFFFFFFFF);
			d.x_draw++;
		}
		d.y_draw++;
	}
}

void	shadow(t_game *game, int x, int y, int size)
{
	t_draw	d;

	d.x_start = x;
	d.y_start = y + size;
	d.x_end = d.x_start + size;
	d.y_end = d.y_start + size / 3;
	d.y_draw = d.y_start;
	while (d.y_draw <= d.y_end)
	{
		d.x_draw = d.x_start;
		while (d.x_draw <= d.x_end + 1)
		{
			put_pixel(game->minimap, d.x_draw, d.y_draw, 0x470D00FF);
			d.x_draw++;
		}
		d.y_draw++;
	}
}

void	draw_square(t_game *game, int x, int y, uint32_t color)
{
	t_draw	d;
	int		size;

	size = game->scale;
	d.x_start = x;
	d.y_start = y;
	d.x_end = x + size;
	d.y_end = y + size;
	d.y_draw = d.y_start;
	while (d.y_draw <= d.y_end)
	{
		d.x_draw = d.x_start - 1;
		while (d.x_draw++ <= d.x_end)
			put_pixel(game->minimap, d.x_draw, d.y_draw, color);
		d.y_draw++;
	}
	shadow(game, x, y, size);
}

void	draw_background(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_width)
	{
		j = 0;
		while (j < game->map_height)
		{
			if (game->map[j][i] == '0' || game->map[j][i] == '#')
				draw_square(game, i * game->scale, j * game->scale, 0xD6C0AB9F);
			j++;
		}
		i++;
	}
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;

	draw_background(game);
	i = 0;
	while (i < game->map_width)
	{
		j = 0;
		while (j < game->map_height)
		{
			if (game->map[j][i] == '1')
				draw_square(game, i * game->scale, j * game->scale, 0x660F07FF);
			j++;
		}
		i++;
	}
	draw_player(game, game->player.x_pos * game->scale - 6, game->player.y_pos
		* game->scale - 6, 12);
	draw_player(game, game->player.x_pos * game->scale - 4, game->player.y_pos
		* game->scale - 4, 8);
}
