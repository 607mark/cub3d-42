/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:12:46 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/04/07 10:50:56 by rkhakimu         ###   ########.fr       */
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

int	check_color_duplicate(char *line, t_game *game)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (game->floor_rgb != -1)
		{
			free(line);
			error_exit("Duplicate (F) color", game);
		}
		return (1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (game->ceiling_rgb != -1)
		{
			free(line);
			error_exit("Duplicate (C) color", game);
		}
		return (2);
	}
	else
	{
		free(line);
		error_exit("Invalid color identifiers (must be F or C)", game);
	}
	return (0);
}

void	normalize_map_rows(t_game *game)
{
	int		i;
	int		current_len;
	char	*padded_row;

	i = 0;
	while (i < game->map_height)
	{
		current_len = ft_strlen(game->map[i]);
		if (current_len < game->map_width)
		{
			padded_row = malloc((game->map_width + 1) * sizeof(char));
			if (!padded_row)
				error_exit("Memory allocation padding", game);
			ft_strlcpy(padded_row, game->map[i], current_len + 1);
			ft_memset(padded_row + current_len,
				'2', game->map_width - current_len);
			padded_row[game->map_width] = '\0';
			free(game->map[i]);
			game->map[i] = padded_row;
		}
		i++;
	}
}
