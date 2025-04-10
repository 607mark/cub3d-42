/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:03:49 by mshabano          #+#    #+#             */
/*   Updated: 2025/04/01 15:53:04 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// x_cam is conversion of i(n of vertical line to number from -1 to 1,
//where it's the leftmost and rightmost ray accordingly
// rays direction calculation is a linear transformation that shifts player's 
//direction by a scaled perpendicular component
void	calc_ray_dir(t_raycast *r, int i, t_game *game)
{
	r->x_cam = 2 * i / (double)game->width - 1;
	r->x_raydir = game->player.x_dir + game->player.x_plane * r->x_cam;
	r->y_raydir = game->player.y_dir + game->player.y_plane * r->x_cam;
}

void	calc_delt_dist(t_raycast *r)
{
	r->x_delt_dist = 1e12;
	r->y_delt_dist = 1e12;
	if (r->x_raydir)
		r->x_delt_dist = fabs(1 / r->x_raydir);
	if (r->y_raydir)
		r->y_delt_dist = fabs(1 / r->y_raydir);
}

void	set_step_dir(t_raycast *r, t_game *game)
{
	r->x_map = (int)game->player.x_pos;
	r->y_map = (int)game->player.y_pos;
	r->x_step = 1;
	r->x_side_dist = (r->x_map + 1 - game->player.x_pos) * r->x_delt_dist;
	r->y_step = 1;
	r->y_side_dist = (r->y_map + 1 - game->player.y_pos) * r->y_delt_dist;
	if (r->x_raydir < 0)
	{
		r->x_step = -1;
		r->x_side_dist = (game->player.x_pos - r->x_map) * r->x_delt_dist;
	}
	if (r->y_raydir < 0)
	{
		r->y_step = -1;
		r->y_side_dist = (game->player.y_pos - r->y_map) * r->y_delt_dist;
	}
}

// side = 0 means hit a vertical wall (x-step),
// side = 1 means hit a horizontal wall (y-step)
void	dda(t_raycast *r, t_game *game)
{
	while (r->collision == false)
	{
		if (r->x_side_dist < r->y_side_dist)
		{
			r->x_side_dist += r->x_delt_dist;
			r->x_map += r->x_step;
			r->side = 0;
		}
		else
		{
			r->y_side_dist += r->y_delt_dist;
			r->y_map += r->y_step;
			r->side = 1;
		}
		if (r->x_map >= 0 && r->x_map < game->map_width && r->y_map >= 0
			&& r->y_map < game->map_height
			&& (game->map[r->y_map][r->x_map] != '#'))
			r->collision = true;
	}
}

void	calc_perpendicular_dist(t_raycast *r)
{
	if (r->side == 0)
		r->perp_dist = (r->x_side_dist - r->x_delt_dist);
	else
		r->perp_dist = (r->y_side_dist - r->y_delt_dist);
}
