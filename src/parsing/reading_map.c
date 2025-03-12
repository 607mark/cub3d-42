/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:47:45 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/12 19:04:57 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static char	**copy_rows(char **new, char **old, int index, int numofrows)
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

void	read_map(t_game *game, int fd)
{
	char	*line;
	char	**temp_map;
	int		height;

	temp_map = NULL;
	height = 0;
	line = get_next_line(fd);
	while (line)
    {
        char *trimmed = ft_strtrim(line, "\n");
        temp_map = ft_realloc_2d(temp_map, height + 1);
        if (!temp_map)
            error_exit("Memory allocation failed");
        temp_map[height] = ft_strdup(trimmed);
        if (!temp_map[height])
            error_exit("Memory allocation failed");
        free(trimmed);
        free(line);
        height++;
        line = get_next_line(fd);
    }
    if (height == 0)
        error_exit("Empty map");
    game->map = temp_map;
    game->map_height = height;
}

void	check_row(char *row, int y, t_game *game, int *player_found)
{
	char	*ptr;
	
	ptr = row;
	while(*ptr)
	{
		if (*ptr == 'N' || *ptr == 'S' || *ptr == 'W' || *ptr == 'E')
		{
			if (*player_found)
				error_exit("Multiple players in map");
			*player_found = 1;
			game->player.x = ptr - row;
			game->player.y = y;
			game->player.orientation = *ptr;
		}
		else if (*ptr != '0' && *ptr != '1' && !ft_isspace(*ptr))
		    error_exit("Invalid character in map");
		ptr++;
	}
}

