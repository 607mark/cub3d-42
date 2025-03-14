/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:51:33 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/14 12:04:12 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	flood_fill(t_game *game, int x, int y, char **map)
{
    printf("x: %d, y: %d, game->map_height: %d, game->map_width: %d\n", x, y, game->map_height, game->map_width);
    if (y < 0 || y >= game->map_height || x < 0 || x >= game->map_width)
        error_exit("Map not enclosed by walls: out of bounds");
    if (map[y][x] == '1' || map[y][x] == '#')
        return ;
    if (ft_isspace(map[y][x]))
        error_exit("Map not enclosed by walls: whitespace at boundary");
    map[y][x] = '#';
    flood_fill(game, x + 1, y, map);
    flood_fill(game, x - 1, y, map);
    flood_fill(game, x, y + 1, map);
    flood_fill(game, x, y - 1, map);
}
