/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 23:30:40 by mshabano          #+#    #+#             */
/*   Updated: 2025/04/09 15:54:53 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	put_pixel(mlx_image_t *image, int x, int y, uint32_t color)
{
	if (x >= (long long)image->width || x < 0)
		return ;
	if (y >= (long long)image->height || y < 0)
		return ;
	mlx_put_pixel(image, x, y, color);
}

int	is_valid_pos(t_game *game, double x, double y)
{
	return (game->map[(int)y][(int)x] == '#');
}

/*if (r->tex_x_pix >= texture->width) r->tex_x_pix = texture->width - 1;
	if (r->tex_y_pix >= texture->height) r->tex_y_pix = texture->height - 1;*/
