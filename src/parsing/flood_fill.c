/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:51:33 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/12 19:00:23 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	flood_fill(t_game *game, int x, int y, char **map)
{
	printf("x: %d, y: %d, game->map_height: %d\n", x, y, game->map_height);
	if (x < 0 || y < 0 || y >= game->map_height)
	{
		
		error_exit("Map not enclosed by walls");
	}
	if (x >= (int)ft_strlen(map[y]))
		error_exit("Map not enclosed by walls, h");
	if (map[y][x] == '1' || map[y][x] == '#')
		return ;
	if (ft_isspace(map[y][x]))
		return ;
	map[y][x] = '#';
	flood_fill(game, x + 1, y, map);
	flood_fill(game, x - 1, y, map);
	flood_fill(game, x, y + 1, map);
	flood_fill(game, x, y - 1, map);
}
