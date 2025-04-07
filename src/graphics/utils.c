/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 23:30:40 by mshabano          #+#    #+#             */
/*   Updated: 2025/04/01 15:53:12 by rkhakimu         ###   ########.fr       */
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
