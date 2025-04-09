/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:47:43 by mshabano          #+#    #+#             */
/*   Updated: 2025/04/09 15:54:57 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

uint32_t	get_tex_pix_color(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	uint32_t	shift;
	uint8_t		*pixel;
	uint32_t	color;

	if (x >= texture->width)
		x = texture-> width - 1;
	shift = (y * texture->width + x) * texture->bytes_per_pixel;
	pixel = texture->pixels + shift;
	color = (pixel[0] << 24 | pixel[1] << 16 | (pixel[2] << 8) | pixel[3]);
	return (color);
}

void	define_side(t_raycast *r)
{
	if (r->side && r->y_raydir < 0)
		r->texture_type = 'N';
	else if (r->side && r->y_raydir >= 0)
		r->texture_type = 'S';
	else if (!r->side && r->x_raydir < 0)
		r->texture_type = 'W';
	else if (!r->side && r->x_raydir >= 0)
		r->texture_type = 'E';
}

void	calc_texture_points(t_game *game, t_raycast *r, int total_y)
{
	r->x_hit = fabs(game->player.x_pos + r->x_raydir * r->perp_dist);
	r->y_hit = fabs(game->player.y_pos + r->y_raydir * r->perp_dist);
	r->tex_x_point = r->y_hit - (int)r->y_hit;
	if (r->side)
		r->tex_x_point = r->x_hit - (int)r->x_hit;
	if (r->texture_type == 'S' || r->texture_type == 'W')
		r->tex_x_point = 1 - r->tex_x_point;
	r->tex_y_point = (double)(total_y - r->draw_start) / (double)r->wall_height;
}

void	calc_tex_pix_coords(t_game *game, t_raycast *r)
{
	if (r->texture_type == 'N')
	{
		r->tex_x_pix = game->textures.tex_north->width * r->tex_x_point;
		r->tex_y_pix = game->textures.tex_north->height * r->tex_y_point;
	}
	else if (r->texture_type == 'S')
	{
		r->tex_x_pix = game->textures.tex_south->width * r->tex_x_point;
		r->tex_y_pix = game->textures.tex_south->height * r->tex_y_point;
	}
	else if (r->texture_type == 'W')
	{
		r->tex_x_pix = game->textures.tex_west->width * r->tex_x_point;
		r->tex_y_pix = game->textures.tex_west->height * r->tex_y_point;
	}
	else
	{
		r->tex_x_pix = game->textures.tex_east->width * r->tex_x_point;
		r->tex_y_pix = game->textures.tex_east->height * r->tex_y_point;
	}
	if (r->tex_x_pix < 0)
		r->tex_x_pix = 0;
	if (r->tex_y_pix < 0)
		r->tex_y_pix = 0;
}

uint32_t	get_color(t_game *game, t_raycast *r, long long total_y)
{
	define_side(r);
	calc_texture_points(game, r, total_y);
	calc_tex_pix_coords(game, r);
	if (r->texture_type == 'N')
		return (get_tex_pix_color(game->textures.tex_north, r->tex_x_pix,
				r->tex_y_pix));
	else if (r->texture_type == 'S')
		return (get_tex_pix_color(game->textures.tex_south, r->tex_x_pix,
				r->tex_y_pix));
	else if (r->texture_type == 'W')
		return (get_tex_pix_color(game->textures.tex_west, r->tex_x_pix,
				r->tex_y_pix));
	else
		return (get_tex_pix_color(game->textures.tex_east, r->tex_x_pix,
				r->tex_y_pix));
}
