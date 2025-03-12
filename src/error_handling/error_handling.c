/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:17:47 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/12 11:09:21 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "../../inc/cub3d.h"

void	error_exit(char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit (1);
}

void	free_game(t_game *game)
{
	int	y;
	
	y = 0;
	while(y < game->map_height)
	{
		free(game->map[y]);
		y++;
	}
	if (game->map)
		free(game->map);
	free(game->textures.north);
	free(game->textures.south);
	free(game->textures.west);
	free(game->textures.east);
	//more for mlx;
}