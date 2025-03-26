/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:10:07 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/26 16:30:29 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_game(t_game *game)
{
	ft_memset(game, 0, sizeof(t_game));
}



int	main(int ac, char **av)
{
	t_game	game;
	if (ac != 2)
		error_exit("Usage: ./cub3d <map.cub>", NULL);
	parse_cub_file(&game, av[1]);
	load_textures(&game);
	//render(&game);
	free_game(&game);
	
	return (0);
}

