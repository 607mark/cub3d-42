/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:26:12 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/19 11:29:45 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	load_north_texture(t_game *game)
{
	mlx_texture_t	*temp;
	
	temp = NULL;
	if (game->textures.north)
	{
		temp = load_texture_file(game->textures.north);
		game->textures.img_north = texture_to_image(game, temp);
	}
}

void	load_south_texture(t_game *game)
{
	mlx_texture_t	*temp;
	
	temp = NULL;
	if (game->textures.south)
	{
		temp = load_texture_file(game->textures.south);
		game->textures.img_south = texture_to_image(game, temp);
	}
}

void	load_west_texture(t_game *game)
{
	mlx_texture_t	*temp;
	
	temp = NULL;
	if (game->textures.west)
	{
		temp = load_texture_file(game->textures.west);
		game->textures.img_west = texture_to_image(game, temp);
	}
}

void	load_east_texture(t_game *game)
{
	mlx_texture_t	*temp;
	
	temp = NULL;
	if (game->textures.east)
	{
		temp = load_texture_file(game->textures.east);
		game->textures.img_east = texture_to_image(game, temp);
	}
}

void	load_textures(t_game *game)
{
	load_north_texture(game);
	load_south_texture(game);
	load_west_texture(game);
	load_east_texture(game);
}
