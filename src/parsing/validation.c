/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:59:07 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/12 12:35:47 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	validate_file_ext(char *filename)
{
	char	*ext;
	
	ext = NULL;
	ext = ft_strrchr(filename, '.');
	if (!ext)
		return (0);
	if (ft_strcmp(".cub", ext) == 0)
		return (1);
	return (0);
}

int	validate_tex_ext(char *filename)
{
	char	*ext;

	ext = NULL;
	ext = ft_strrchr(filename, '.');
	if (!ext)
		return (0);
	if (ft_strcmp(".xpm", ext) == 0 || ft_strcmp(".png", ext) == 0)
		return (1);
	return (0);
}


int	validate_file_access(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	is_config_element(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
			ft_strncmp(line, "WE ", 3) ==0 || ft_strncmp(line, "EA ", 3) == 0 ||
			ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
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
		if (ft_strlen(game->map[y]) > game->map_width)
			game->map_width = ft_strlen(game->map[y]);
		y++;
	}
	if (!player_found)
		error_exit("No player found in map");
	flood_fill(game, game->player.x, game->player.y, game->map);
}
