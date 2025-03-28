#include "../../inc/cub3d.h"

// x_cam is conversion of i(n of vertical line to number from -1 to 1, where it's the leftmost and rightmost ray accordingly
// rays direction calculation is a linear transformation that shifts player's direction by a scaled perpendicular component 
void calc_ray_dir(t_raycast *r, int i, t_game* game)
{
    r->x_cam = 2 * i / (double) game->width - 1;
    r->x_raydir = game->player.x_dir + game->player.x_plane * r->x_cam;
    r->y_raydir = game->player.y_dir + game->player.y_plane * r->x_cam;
}

// delt_dist is the distance it takes ray to cross 1 "square" on xy graph, it's 1 <=
void calc_delt_dist(t_raycast *r, int i, t_game* game)
{
    if (!r->x_raydir) //check if the ray is moving this direction at all, if no, then set to big value to prevent division by 0 later on
        r->x_delt_dist = 1e12;
    else
        r->x_delt_dist = fabs(1/r->x_raydir); // fabs is |-4| = 4
    if (!r->y_raydir)
        r->y_delt_dist = 1e12;
    else
        r->y_delt_dist = fabs(1/r->y_raydir);
}


//determines step's direction for future dda calculation
// side_dist is calculation to get the distance to the closest whole number coord.  if 3.65 -> calc distance to get to 4
//if ray direction for one of the axises was 0, then delt_dist is 1e12, then side_dist is also really big, this is used in later dda , so dda will never pick this step
void get_step_dir(t_raycast *r, int i, t_game* game)
{
    r->x_map = (int)game->player.x_pos;
    r->y_map = (int)game->player.y_pos;
    if (r->x_raydir < 0)
    {
        r->x_step = -1;
        r->x_side_dist = (game->player.x_pos - r->x_map) * r->x_delt_dist;
    }
    else
    {
        r->x_step = 1;
        r->x_side_dist = (r->x_map + 1 - game->player.x_pos) * r->x_delt_dist;
    }
    if (r->y_raydir < 0)
    {
        r->y_step = -1;
        r->y_side_dist = (game->player.y_pos - r->y_map) * r->y_delt_dist;
    }
    else
    {
        r->y_step = 1;
        r->y_side_dist = (r->y_map + 1 - game->player.y_pos) * r->y_delt_dist;
    }
}

// moves the ray step-by-step across the map to find where it hits a wall
// compares x_side_dist and y_side_dist to decide which direction to step next (x or y)
// if a step’s side_dist was huge (1e12 from delt_dist), dda skips that direction, doing only on the valid step
// side = 0 means hit a vertical wall (x-step), side = 1 means hit a horizontal wall (y-step)
void dda(t_raycast *r, t_game* game)
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
        if (r->x_map >= 0 && r->x_map < game->map_width && r->y_map >= 0 && r->y_map < game->map_height)
        {
            if (game->map[r->y_map][r->x_map] != '#')
                r->collision = true;
        }
    }
}


void calc_perpendicular_dist(t_raycast *r)
{
    if (r->side == 0)
        r->perp_dist = (r->x_side_dist - r->x_delt_dist);
    else
        r->perp_dist = (r->y_side_dist - r->y_delt_dist);
}
