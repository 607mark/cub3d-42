/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:59:25 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/27 13:27:50 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	read_config_line(t_game *game, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		error_exit("Memory allocation failed", game);
	free(line);
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		parse_texture(&game->textures, trimmed, game);
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		parse_texture(&game->textures, trimmed, game);
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		parse_texture(&game->textures, trimmed, game);
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		parse_texture(&game->textures, trimmed, game);
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
		parse_color(&game->floor_rgb, trimmed, game);
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		parse_color(&game->ceiling_rgb, trimmed, game);
	else
	{
		free(trimmed);
		error_exit("Invalid config line", game);
	}
}



void	parse_cub_file(t_game *game, char *filename)
{
	int		fd;
	char	*first_map_line;

	init_game(game);
	if (!validate_file_ext(filename) || !validate_file_access(filename))
		error_exit("Invalid file extension or access", game);
	game->fd = open(filename, O_RDONLY);
	if (game->fd < 0)
		error_exit("Failed to open a file", game);
	first_map_line = parse_config(game, game->fd);
	parse_map_start(game, game->fd, first_map_line);
	close(game->fd);
	validate_config(game);
	validate_map(game);
}

char	*parse_config(t_game *game, int fd)
{
	char	*line;
	line = get_next_line(fd);
	while (line && (is_config_element(line) || is_newline(line)))
	{
		if (is_config_element(line))
			read_config_line(game, line);
		else
			free(line);
		line = get_next_line(fd);
	}
	if (!line)
		error_exit("No map found in file", game);
	return (line);
}

void	parse_map_start(t_game *game, int fd, char *first_map_line)
{
    char *line;
    char *trimmed;

    line = first_map_line;
    while (line && is_newline(line))
    {
        free(line);
        line = get_next_line(fd);
    }
    if (!line)
        error_exit("No map found after config", game);
    game->map = ft_realloc_2d(NULL, 1);
    if (!game->map)
	{
		free(line);
        error_exit("Memory allocation failed", game);
	}
    trimmed = ft_strtrim(line, "\n");
    if (!trimmed)
	{
		free(line);
        error_exit("Memory allocation failed", game);
	}
    game->map[0] = trimmed;
    free(line);
    game->map_height = 1;
    read_map(game, fd);
}

void	parse_texture(t_texture *textures, char *line, t_game *game)
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
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (textures->north)
		{
			free(path);
			free(line);
			error_exit("Duplicate NO textrure", game);
		}
		textures->north = path;
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
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (textures->west)
		{
			free(path);
			free(line);
			error_exit("Duplicate WE textrure", game);
		}
		textures->west = path;
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
	}
	free(line);
}
