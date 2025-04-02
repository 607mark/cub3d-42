/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:09:02 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/04/02 10:09:48 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

char	*extract_texture_path(char *line, t_game *game)
{
	char	*path;
	char	*start;

	start = line + 3;
	while (ft_isspace(*start))
		start++;
	path = ft_strdup(start);
	if (!path)
	{
		free(line);
		error_exit("Memory allocation failed", game);
	}
	if (!validate_tex_ext(path, game))
	{
		free(path);
		free(line);
		error_exit("Invalid texture extention (must be teture.png)", game);
	}
	if (!validate_file_access(path))
	{
		free(path);
		free(line);
		error_exit("File not accessible", game);
	}
	return (path);
}

int	assign_north_south_texture(t_texture *textures,
		char *line, char *path, t_game *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (textures->north)
		{
			free(path);
			free(line);
			error_exit("Duplicate NO textrure", game);
		}
		textures->north = path;
		return (1);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (textures->south)
		{
			free(path);
			free(line);
			error_exit("Duplicate SO textrure", game);
		}
		textures->south = path;
		return (1);
	}
	return (0);
}

int	assign_east_west_texture(t_texture *textures,
		char *line, char *path, t_game *game)
{
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (textures->west)
		{
			free(path);
			free(line);
			error_exit("Duplicate WE textrure", game);
		}
		textures->west = path;
		return (1);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (textures->east)
		{
			free(path);
			free(line);
			error_exit("Duplicate EA textrure", game);
		}
		textures->east = path;
		return (1);
	}
	return (0);
}

void	parse_texture(t_texture *textures, char *line, t_game *game)
{
	char	*path;

	path = extract_texture_path(line, game);
	if (assign_north_south_texture(textures, line, path, game))
	{
		free(line);
		return ;
	}
	if (assign_east_west_texture(textures, line, path, game))
	{
		free(line);
		return ;
	}
	free(path);
	free(line);
}
