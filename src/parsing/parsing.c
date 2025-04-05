/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:59:25 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/04/02 12:04:26 by rkhakimu         ###   ########.fr       */
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
	char	*first_map_line;

	init_game(game);
	if (!validate_file_ext(filename) || !validate_file_access(filename))
		error_exit("Invalid file extension or access", game);
	game->fd = open(filename, O_RDONLY);
	if (game->fd < 0)
		error_exit("Failed to open a file", game);
	first_map_line = parse_config(game, game->fd);
	parse_map_start(game, game->fd, first_map_line);
	validate_config(game);
	validate_map(game);
	close(game->fd);
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
		error_exit("Invalid map", game);
	return (line);
}

char	*skip_empty_lines(int fd, char *first_map_line)
{
	char	*line;

	line = first_map_line;
	while (line && is_newline(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

void	parse_map_start(t_game *game, int fd, char *first_map_line)
{
	char	*line;
	char	*trimmed;

	line = skip_empty_lines(fd, first_map_line);
	if (!line)
		error_exit("Invalid map", game);
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
		error_exit("Memoory allocation failed", game);
	}
	game->map[0] = trimmed;
	free(line);
	game->map_height = 1;
	if (game->map_height > 128)
		error_exit("Map exceeds height limit (128)", game);
	read_map(game, fd);
}
