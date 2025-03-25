#include "../../inc/cub3d.h"


uint32_t get_color(t_game * game, t_raycast *r)
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
    
    if (r->texture_type == 'N')
        return (4278190335);
    if (r->texture_type == 'S')
        return (65280);
    if (r->texture_type == 'W')
        return (255);
    if (r->texture_type == 'E')
        return (4294967295);
}