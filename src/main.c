/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:10:07 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/04/01 17:52:48 by rkhakimu         ###   ########.fr       */
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
		error_exit("Usage: ./cub3d <map.cub>", NULL);
	parse_cub_file(&game, av[1]);
	load_textures(&game);
	render(&game);
	free_game(&game);
	return (0);
}
