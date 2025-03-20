/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:54:57 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/20 09:35:09 by rkhakimu         ###   ########.fr       */
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

void	free_texture_pair(char **path, mlx_texture_t **texture)
{
	if (*path)
	{
		free(*path);
		*path = NULL;
	}
	if (*texture)
	{
		free(*texture);
		*texture = NULL;
	}
}

void	free_textures(t_game *game)
{
	free_texture_pair(&game->textures.north, &game->textures.tex_north);
	free_texture_pair(&game->textures.south, &game->textures.tex_south);
	free_texture_pair(&game->textures.west, &game->textures.tex_west);
	free_texture_pair(&game->textures.east, &game->textures.tex_east);
}

void	free_mlx_images(t_game *game)
{
	if (game->textures.tex_north)
	{
		mlx_delete_image(game->mlx, game->textures.tex_north);
		game->textures.tex_north = NULL;
	}
	if (game->textures.tex_south)
	{
		mlx_delete_image(game->mlx, game->textures.tex_south);
		game->textures.tex_south = NULL;
	}
	if (game->textures.tex_west)
	{
		mlx_delete_image(game->mlx, game->textures.tex_west);
		game->textures.tex_west = NULL;
	}
	if (game->textures.tex_east)
	{
		mlx_delete_image(game->mlx, game->textures.tex_east);
		game->textures.tex_east = NULL;
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
