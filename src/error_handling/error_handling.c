/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:17:47 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/27 12:57:12 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	error_exit(char *msg, t_game *game)
{
	char *line;

	line = NULL;
	if (game && game->fd != -1)
	{
		line = get_next_line(game->fd);
		while (line)
		{
			free(line);
			line = get_next_line(game->fd);
		}
		close(game->fd);
	}
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free_game(game);
	exit (1);
}
