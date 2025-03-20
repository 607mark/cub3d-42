/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:26:12 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/20 09:34:42 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

mlx_texture_t	*load_texture_file(char *path)
{
	mlx_texture_t	*texture;

	if (!path || !validate_tex_ext(path))
		error_exit("invalid texture path or extention");
	texture = mlx_load_png(path);
	if (!texture)
		error_exit("Failed to load PNG texture");
	return (texture);    
}

void	load_textures(t_game *game)
{
	if (game->textures.north)
		error_exit("Missing NO texture");
	game->textures.tex_north = load_texture_file(game->textures.north);
	if (game->textures.south)
		error_exit("Missing SO texture");
	game->textures.tex_south = load_texture_file(game->textures.south);
	if (game->textures.west)
		error_exit("Missing WE texture");
	game->textures.tex_west = load_texture_file(game->textures.west);
	if (game->textures.east)
		error_exit("Missing EA texture");
	game->textures.tex_east = load_texture_file(game->textures.east);

}
