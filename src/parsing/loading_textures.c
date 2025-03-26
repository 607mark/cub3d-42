/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:26:12 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/26 15:59:16 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

mlx_texture_t	*load_texture_file(char *path, t_game *game)
{
	mlx_texture_t	*texture;

	if (!path || !validate_tex_ext(path, game))
		error_exit("invalid texture path or extention", game);
	texture = mlx_load_png(path);
	if (!texture)
		error_exit("Failed to load PNG texture", game);
	return (texture);    
}

void	load_textures(t_game *game)
{
	if (!game->textures.north)
		error_exit("Missing NO texture", game);
	game->textures.tex_north = load_texture_file(game->textures.north, game);
	if (!game->textures.south)
		error_exit("Missing SO texture", game);
	game->textures.tex_south = load_texture_file(game->textures.south, game);
	if (!game->textures.west)
		error_exit("Missing WE texture", game);
	game->textures.tex_west = load_texture_file(game->textures.west, game);
	if (!game->textures.east)
		error_exit("Missing EA texture", game);
	game->textures.tex_east = load_texture_file(game->textures.east, game);

}

// mlx_texture_t	*get_texture_for_wall(t_game *game, t_raycast *raycast)
// {
// 	mlx_texture_t	*texture;

// 	if (raycast->side == 0)
// 	{
// 		if (raycast->x_raydir > 0)
// 			texture = game->textures.east;
// 		else
// 			texture = game->textures.west;
// 	}
// 	else
// 	{
// 		if (raycast->y_raydir > 0)
// 			texture = game->textures.south;
// 		else
// 			texture = game->textures.north;
// 	}
// 	return (texture);
// }
