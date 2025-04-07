/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:59:07 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/04/07 10:42:47 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_config_element(char *line)
{
	char	*trimmed;

	if (!line)
		return (0);
	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		return (0);
	if (ft_strncmp(trimmed, "NO ", 3) == 0
		|| ft_strncmp(trimmed, "SO ", 3) == 0
		|| ft_strncmp(trimmed, "WE ", 3) == 0
		|| ft_strncmp(trimmed, "EA ", 3) == 0
		|| ft_strncmp(trimmed, "F ", 2) == 0
		|| ft_strncmp(trimmed, "C ", 2) == 0)
	{
		free(trimmed);
		return (1);
	}
	free(trimmed);
	return (0);
}

void	validate_map(t_game *game)
{
	int	y;
	int	player_found;

	y = 0;
	player_found = 0;
	while (y < game->map_height)
	{
		check_row(game->map[y], y, game, &player_found);
		if ((int)ft_strlen(game->map[y]) > game->map_width)
			game->map_width = ft_strlen(game->map[y]);
		y++;
	}
	if (!player_found)
		error_exit("No player found in map", game);
	if (game->map_width < 2)
		error_exit("Map too narrow", game);
	normalize_map_rows(game);
	flood_fill(game, game->player.x_pos, game->player.y_pos, game->map);
}

void	validate_config(t_game *game)
{
	if (!game->textures.north)
		error_exit("Missing NO texture", game);
	if (!game->textures.south)
		error_exit("Missing SO texture", game);
	if (!game->textures.west)
		error_exit("Missing WE texture", game);
	if (!game->textures.east)
		error_exit("Missing EA texture", game);
	if (game->ceiling_rgb == -1)
		error_exit("Missing C color", game);
	if (game->floor_rgb == -1)
		error_exit("Missing F color", game);
}
