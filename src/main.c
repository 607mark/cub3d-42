/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:10:07 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/11 13:38:35 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_game(t_game *game)
{
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->player.x = 0.0;
	game->player.y = 0.0;
	game->player.dir_x = 0.0;
	game->player.dir_y = 0.0;
	game->player.orientation = '\0';
	game->textures.north = NULL;
	game->textures.south = NULL;
	game->textures.west = NULL;
	game->textures.east = NULL;
	game->textures.img_north = NULL;
	game->textures.img_south = NULL;
	game->textures.img_west = NULL;
	game->textures.img_east = NULL;
	game->floor_rgb = -1;
	game->ceiling_rgb = -1;
	game->img_ptr = NULL;
	game->mlx_ptr = NULL;
}

int	main(int ac, char **av)
{
	t_game	game;
	if (ac != 2)
		error_exit("Usage: ./cub3d <map.cub>");
	parse_cub_file(&game, argv[1]);
	free_game(&game);
	return (0);
}

