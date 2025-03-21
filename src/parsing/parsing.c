/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:59:25 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/20 14:10:22 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	read_config_line(t_game *game, char *line)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		error_exit("Memory allocation failed");
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		parse_texture(&game->textures, trimmed);
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		parse_texture(&game->textures, trimmed);
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		parse_texture(&game->textures, trimmed);
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		parse_texture(&game->textures, trimmed);
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
		parse_color(&game->floor_rgb, trimmed);
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		parse_color(&game->ceiling_rgb, trimmed);
	else
		error_exit("invalid config line");
	free(trimmed);
}

void	parse_cub_file(t_game *game, char *filename)
{
	int		fd;
	char	*first_map_line;

	if (!validate_file_ext(filename) || !validate_file_access(filename))
		error_exit("Invalid file extension or access");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open a file");
	init_game(game);
	first_map_line = parse_config(game, fd);
	parse_map_start(game, fd, first_map_line);
	close(fd);
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
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
	{
		free(line);
		error_exit("No map found in file");
	}
	return (line);
}

void	parse_map_start(t_game *game, int fd, char *first_map_line)
{
	char	*line;

	line = first_map_line;
	while (line && is_newline(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		error_exit("No map found after config");
	game->map = ft_realloc_2d(NULL, 1);
	game->map[0] = ft_strdup(ft_strtrim(line, "\n"));
	game->map_height = 1;
	free(line);
	read_map(game, fd);
}

void	parse_texture(t_texture *textures, char *line)
{
	char	*path;
	char	*start;

	start = line + 3;
	while (ft_isspace(*start))
		start++;
	path = ft_strdup(start);
	if (!path)
		error_exit("Memory allocation failed");
	if (!validate_tex_ext(path))
	{
		free(path);
		error_exit("Invalid texture extention (must be teture.png)");
	}
	if (!validate_file_access(path))
	{
		free(path);
		error_exit("File not accessible");
	}
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (textures->north)
			error_exit("Duplicate NO textrure");
		textures->north = path;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (textures->south)
			error_exit("Duplicate SO textrure");
		textures->south = path;
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (textures->west)
			error_exit("Duplicate WE textrure");
		textures->west = path;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (textures->east)
			error_exit("Duplicate EA textrure");
		textures->east = path;
	}
}
