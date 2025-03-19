/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:54:57 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/19 13:11:34 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_map(t_game *game)
{
	int	y;
	
	y = 0;
	if (game->map)
	{
		while (y < game->map_height)
		{
			if (game->map[y])
				free(game->map[y]);
			y++;
		}
		free(game->map);
		game->map = NULL;
	}
}

void	free_textures(t_game *game)
{
	if (game->textures.north)
	{
		free(game->textures.north);
		game->textures.north = NULL;
	}
	if (game->textures.south)
	{
		free(game->textures.south);
		game->textures.south = NULL;
	}
	if (game->textures.east)
	{
		free(game->textures.east);
		game->textures.east = NULL;
	}
	if (game->textures.west)
	{
		free(game->textures.west);
		game->textures.west = NULL;
	}
}

void	free_mlx_images(t_game *game)
{
	if (game->textures.img_north)
	{
		mlx_delete_image(game->mlx, game->textures.img_north);
		game->textures.img_north = NULL;
	}
	if (game->textures.img_south)
	{
		mlx_delete_image(game->mlx, game->textures.img_south);
		game->textures.img_south = NULL;
	}
	if (game->textures.img_west)
	{
		mlx_delete_image(game->mlx, game->textures.img_west);
		game->textures.img_west = NULL;
	}
	if (game->textures.img_east)
	{
		mlx_delete_image(game->mlx, game->textures.img_east);
		game->textures.img_east = NULL;
	}
}

void	free_mlx(t_game *game)
{
	if (game->img)
	{
		mlx_delete_image(game->mlx, game->img);
		game->img = NULL;
	}
	if (game->mlx)
	{
		mlx_terminate(game->mlx);
		game->mlx = NULL;
	}
}

void	free_game(t_game *game)
{
	free_map(game);
	free_textures(game);
	free_mlx_images(game);
	free_mlx(game);
}
