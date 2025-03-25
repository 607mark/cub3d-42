#include "../../inc/cub3d.h"


uint32_t get_texture_pixel_color(mlx_texture_t* texture, uint32_t x, uint32_t y) {
   
    uint32_t shift = (y * texture->width + x) * texture->bytes_per_pixel;
    uint8_t* pixel = texture->pixels + shift;
    uint32_t color = (pixel[0] << 24 | pixel[1] << 16 | (pixel[2] << 8) | pixel[3]);
    return color;
}

uint32_t get_color(t_game * game, t_raycast *r, int total_y, int draw_start)
{
    double hit_x, hit_y;
    
    hit_x = game->player.x_pos + r->x_raydir * r->perp_dist;
    hit_y = game->player.y_pos + r->y_raydir * r->perp_dist;

    if (r->side && r->y_raydir < 0)
        r->texture_type = 'N';
    else if (r->side && r->y_raydir >= 0)
        r->texture_type = 'S';
    else if (!r->side && r->x_raydir < 0)
        r->texture_type = 'W';
    else if (!r->side && r->x_raydir >= 0)
        r->texture_type = 'E';
    
    double tex_x_point;   
    double tex_y_point; 
    hit_x = fabs(hit_x);
    hit_y = fabs(hit_y);
    
    if (r->side)
        tex_x_point = hit_x - (int)hit_x;
    else
        tex_x_point = hit_y - (int)hit_y;

    tex_y_point = (double)(total_y - draw_start) / (double)r->wall_height;

    int x = game->textures.tex_north->width * tex_x_point;
    int y = game->textures.tex_north->height * tex_y_point;
    if (r->texture_type == 'N')  
        return (get_texture_pixel_color(game->textures.tex_north, x, y));
    if (r->texture_type == 'S')
        return (get_texture_pixel_color(game->textures.tex_south, x, y));
    if (r->texture_type == 'W')
        return (get_texture_pixel_color(game->textures.tex_west, x, y));
    if (r->texture_type == 'E')
        return (get_texture_pixel_color(game->textures.tex_east, x, y));
    
}