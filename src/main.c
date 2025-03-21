/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:10:07 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/20 14:11:02 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_game(t_game *game)
{
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->player.x_pos = 0.0;
	game->player.y_pos = 0.0;
	game->player.x_dir = 0.0;
	game->player.y_dir = 0.0;
	game->player.orientation = '\0';
	game->textures.north = NULL;
	game->textures.south = NULL;
	game->textures.west = NULL;
	game->textures.east = NULL;
	game->textures.tex_north = NULL;
	game->textures.tex_south = NULL;
	game->textures.tex_west = NULL;
	game->textures.tex_east = NULL;
	game->floor_rgb = -1;
	game->ceiling_rgb = -1;
	game->mlx = NULL;
	game->img = NULL;
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
}



int	main(int ac, char **av)
{
	t_game	game;
	if (ac != 2)
		error_exit("Usage: ./cub3d <map.cub>");
	parse_cub_file(&game, av[1]);
	free_game(&game);
	//load_textures(&game);
	return (0);
}

