#include "../../inc/cub3d.h"

uint32_t get_texture_pixel_color(mlx_texture_t* texture, uint32_t x, uint32_t y)
{
    uint32_t shift = (y * texture->width + x) * texture->bytes_per_pixel;
    uint8_t* pixel = texture->pixels + shift;
    uint32_t color = (pixel[0] << 24 | pixel[1] << 16 | (pixel[2] << 8) | pixel[3]);
    return color;
}

void define_side(t_raycast *r)
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

uint32_t get_color(t_game * game, t_raycast *r, int total_y, int draw_start)
{
    double hit_x, hit_y;
    
    hit_x = fabs(game->player.x_pos + r->x_raydir * r->perp_dist);
    hit_y = fabs(game->player.y_pos + r->y_raydir * r->perp_dist);

    define_side(r);
    double tex_x_point;   
    double tex_y_point; 

    if (r->side)
        tex_x_point = hit_x - (int)hit_x;
    else
        tex_x_point = hit_y - (int)hit_y;

    if (r->texture_type == 'S' || r->texture_type == 'W')
        tex_x_point = 1 - tex_x_point;
    tex_y_point = (double)(total_y - draw_start) / (double)r->wall_height;
    if (r->texture_type == 'N')
    {
        int x = game->textures.tex_north->width * tex_x_point;
        int y = game->textures.tex_north->height * tex_y_point;
        return (get_texture_pixel_color(game->textures.tex_north, x, y));
    }
    if (r->texture_type == 'S')
    {
        int x = game->textures.tex_south->width * tex_x_point;
        int y = game->textures.tex_south->height * tex_y_point;
        return (get_texture_pixel_color(game->textures.tex_south, x, y));
    }
    if (r->texture_type == 'W')
    {
        int x = game->textures.tex_west->width * tex_x_point;
        int y = game->textures.tex_west->height * tex_y_point;
        return (get_texture_pixel_color(game->textures.tex_west, x, y));
    }
    else
    {
        int x = game->textures.tex_east->width * tex_x_point;
        int y = game->textures.tex_east->height * tex_y_point;
        return (get_texture_pixel_color(game->textures.tex_east, x, y));
    }
    
}