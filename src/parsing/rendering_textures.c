/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:31:30 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/19 14:34:57 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

mlx_texture_t	*load_texture_file(char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		error_exit("Failed to load PNG texture");
	// for(size_t i = 0; i < texture->height; i++) {
	// 	for(size_t j = 0; j < texture->width; j++) {
	// 		printf("%s", texture->pixels);
	// 	}
	// 	printf("\n");
	// }
	return (texture);    
}
mlx_image_t	*texture_to_image(t_game *game, mlx_texture_t *texture)
{
	mlx_image_t	*image;

	image = mlx_texture_to_image(game->mlx, texture);
	if (!image)
		error_exit("Failed to convert texture to image");
	mlx_delete_texture(texture);
	return (image);
}
