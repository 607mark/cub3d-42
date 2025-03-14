/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:59:07 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/14 17:19:20 by rkhakimu         ###   ########.fr       */
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
	char	*trimmed;
	
	if (!line)
		return (0);
	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		return (0);
	if (ft_strncmp(trimmed, "NO ", 3) == 0 ||
		ft_strncmp(trimmed, "SO ", 3) == 0 ||
		ft_strncmp(trimmed, "WE ", 3) == 0 ||
		ft_strncmp(trimmed, "EA ", 3) == 0 ||
		ft_strncmp(trimmed, "F ", 2) == 0 ||
		ft_strncmp(trimmed, "C ", 2) == 0)
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
        printf("Row %d: %s\n", y, game->map[y]);
        check_row(game->map[y], y, game, &player_found);
        if ((int)ft_strlen(game->map[y]) > game->map_width)
            game->map_width = ft_strlen(game->map[y]);
        y++;
    }
    if (!player_found)
        error_exit("No player found in map");
    printf("Starting flood_fill at x: %f, y: %f\n", game->player.x, game->player.y);
    flood_fill(game, game->player.x, game->player.y, game->map);
}

void	validate_config(t_game *game)
{
	if (!game->textures.north)
		error_exit("Missing NO texture");
	if (!game->textures.south)
		error_exit("Missing SO texture");
	if (!game->textures.west)
		error_exit("Missing WE texture");
	if (!game->textures.east)
		error_exit("Missing EA texture");
	if (game->ceiling_rgb == -1)
		error_exit("Missing C color");
	if (game->floor_rgb == -1)
		error_exit("Missing F color");
}

int	is_newline(char *line)
{
	if (!line)
		return (0);
	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (1);
	return (0);
}
