/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:10:07 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/04/02 17:13:42 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_game(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->fd = -1;
	game->ceiling_rgb = -1;
	game->floor_rgb = -1;
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nUsage: ./cub3d <map.cub>\n", STDERR_FILENO);
		return (1);
	}
	parse_cub_file(&game, av[1]);
	load_textures(&game);
	render(&game);
	free_game(&game);
	return (0);
}
