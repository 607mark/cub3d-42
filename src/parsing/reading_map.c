/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:47:45 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/04/02 12:05:10 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	check_empty_lines_after_map(int fd, t_game *game, int has_content)
{
	char	*line;

	if (!has_content)
		error_exit("Invalid map", game);
	line = get_next_line(fd);
	while (line)
	{
		if (!is_newline(line))
		{
			free(line);
			error_exit("Invalid map", game);
		}
		free(line);
		line = get_next_line(fd);
	}
}

char	*process_map_line(char *line, t_game *game)
{
	if (is_config_element(line))
	{
		free(line);
		error_exit("Invalid map", game);
	}
	return (line);
}

int	add_line_to_map(t_game *game, char *processed_line)
{
	game->map = ft_realloc_2d(game->map, game->map_height + 1);
	if (!game->map)
	{
		free(processed_line);
		error_exit("Memory allocation failed", game);
	}
	game->map[game->map_height] = ft_smartdup(processed_line);
	free(processed_line);
	if (!game->map[game->map_height])
		error_exit("Memory allocation failed", game);
	game->map_height++;
	return (1);
}

void	read_map(t_game *game, int fd)
{
	char	*line;
	char	*processed_line;
	int		has_content;

	has_content = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (is_newline(line))
		{
			free(line);
			check_empty_lines_after_map(fd, game, has_content);
			break ;
		}
		processed_line = process_map_line(line, game);
		if (ft_strlen(processed_line) > 128)
			error_exit("Map exceeds width limit (128)", game);
		has_content = add_line_to_map(game, processed_line);
		if (game->map_height > 128)
			error_exit("Map exceeds height limit (128)", game);
		line = get_next_line(fd);
	}
	if (game->map_height < 2)
		error_exit("Map too small", game);
}

void	check_row(char *row, int y, t_game *game, int *player_found)
{
	char	*ptr;

	ptr = row;
	while (*ptr)
	{
		if (*ptr == 'N' || *ptr == 'S' || *ptr == 'W' || *ptr == 'E')
		{
			if (*player_found)
				error_exit("Multiple players in map", game);
			*player_found = 1;
			game->player.x_pos = ptr - row;
			game->player.y_pos = y;
			game->player.orientation = *ptr;
		}
		else if (*ptr != '0' && *ptr != '1' && !ft_isspace(*ptr))
			error_exit("Invalid character in map", game);
		ptr++;
	}
}
