/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:47:45 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/04/01 17:49:08 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	**copy_rows(char **new, char **old, int index, int numofrows)
{
	if (index >= numofrows)
		return (new);
	new[index] = old[index];
	return (copy_rows(new, old, index + 1, numofrows));
}

char	**ft_realloc_2d(char **old, int new_size)
{
	char	**new;

	new = malloc(new_size * sizeof(char *));
	if (!new)
		return (NULL);
	if (old)
	{
		new = copy_rows(new, old, 0, new_size - 1);
		free(old);
	}
	return (new);
}

void	check_empty_lines_after_map(int fd, t_game *game, int has_content)
{
	char	*line;

	if (!has_content)
		error_exit("Invalid map: empty line within map", game);
	line = get_next_line(fd);
	while (line)
	{
		if (!is_newline(line))
		{
			free(line);
			error_exit("Invalid map: content after map end", game);
		}
		free(line);
		line = get_next_line(fd);
	}
}

char	*process_map_line(char *line, t_game *game)
{
	// char	*trimmed;
		
	// trimmed = ft_strtrim(line, " \t\n");
	// free(line);
	// if (!trimmed)
	// 	error_exit("Trim failed", game);
	if (is_config_element(line))
	{
		free(line);
		error_exit("Invalid map: config element after map start", game);
	}
	return (line);
}

char	*ft_smartdup(const char *s1)
{
	int		i;
	int		len;
	char	*pnt;

	i = 0;
	len = ft_strlen(s1);
	pnt = ft_calloc(129, 1);
	if (!pnt)
		return (NULL);
	while (i < len)
	{
		pnt[i] = s1[i];
		i++;
	}
	pnt[i] = '\0';
	return (pnt);
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
