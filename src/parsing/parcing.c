/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:59:25 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/09 21:34:17 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	parce_cub_file(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	
	if (!validate_file_ext(filename) || !validate_file_access(filename))
		error_exit("Invalid file extension or access");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file");
	init_game(game);
	line = get_next_line(fd);
	while (line && is_config_element(line))
	{
		//reading configuration line function
		free(line);
		line = get_next_line(line);
	}
	if (!line)
		error_exit("No map found in file");
	//reading map function
	free(line);
	close(fd);
	//validating map function
}
