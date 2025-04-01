/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:26:12 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/04/01 11:51:00 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	load_texture_file(char *path, mlx_texture_t **texture, t_game *game)
{
	*texture = mlx_load_png(path);
	if (!*texture)
		error_exit("Failed to load PNG texture", game);
	free(path);
}

void	load_textures(t_game *game)
{
	load_texture_file(game->textures.north, &game->textures.tex_north, game);
	load_texture_file(game->textures.south, &game->textures.tex_south, game);
	load_texture_file(game->textures.west, &game->textures.tex_west, game);
	load_texture_file(game->textures.east, &game->textures.tex_east, game);
}
