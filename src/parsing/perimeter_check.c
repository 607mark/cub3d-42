/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perimeter_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:51:33 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/04/01 11:59:39 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	check_perimeter(t_game *game, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (map[y][x])
		{
			if (y == 0 || y == game->map_height - 1 || x == 0 || x == game->map_width - 1)
			{
				if (map[y][x] != '1')
					error_exit("Map not enclosed: perimeter breach", game);
			}
			x++;
		}
		y++;
	}
}
