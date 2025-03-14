/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 23:47:45 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/14 17:17:13 by rkhakimu         ###   ########.fr       */
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
    int		has_content;
	int		i;
	char	*trimmed;

    has_content = 0;
    line = get_next_line(fd);
    while (line)
    {
        if (is_newline(line))
        {
            free(line);
            if (!has_content)
                error_exit("Invalid map: empty line within map");
            break;
        }
        if (is_config_element(line))
            error_exit("Invalid map: config element after map start");
        trimmed = ft_strtrim(line, "\n");
		i = 0;
		while (trimmed[i])
		{
			if (ft_isspace(trimmed[i]))
				trimmed[i] = '0';
			i++;
		}
        game->map = ft_realloc_2d(game->map, game->map_height + 1);
        if (!game->map)
            error_exit("Memory allocation failed");
        game->map[game->map_height] = ft_strdup(trimmed);
        if (!game->map[game->map_height])
            error_exit("Memory allocation failed");
        free(trimmed);
        free(line);
        game->map_height++;
        has_content = 1;
        line = get_next_line(fd);
    }
    if (game->map_height < 2)
        error_exit("Map too small");
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

