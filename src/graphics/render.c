#include "../../inc/cub3d.h"

// rotation matrix for wikipedia
void rotate_vector(double* x, double* y, double rad)
{
    double x_old = *x;
    double cos_angle = cos(rad);
    double sin_angle = sin(rad);
    *x = x_old * cos_angle - *y * sin_angle;
    *y = x_old * sin_angle + *y * cos_angle;
}

void key_hook(mlx_key_data_t keydata, void* param)
{
    t_game* game = (t_game*)param;
    if (keydata.key == MLX_KEY_W)
        game->keys.w = (keydata.action != MLX_RELEASE);
    if (keydata.key == MLX_KEY_S)
        game->keys.s = (keydata.action != MLX_RELEASE);
    if (keydata.key == MLX_KEY_A)
        game->keys.a = (keydata.action != MLX_RELEASE);
    if (keydata.key == MLX_KEY_D)
        game->keys.d = (keydata.action != MLX_RELEASE);
    if (keydata.key == MLX_KEY_LEFT)
        game->keys.left = (keydata.action != MLX_RELEASE);
    if (keydata.key == MLX_KEY_RIGHT)
        game->keys.right = (keydata.action != MLX_RELEASE);
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(game->mlx);
}

void print_hook(void *param)
{
    t_game* game = (t_game*)param;

    printf("  Pos: (%.2f, %.2f)\n", game->player.x_pos, game->player.y_pos);
    printf("  Dir: (%.2f, %.2f)\n", game->player.x_dir, game->player.y_dir);
    printf("  Plane: (%.2f, %.2f)\n", game->player.x_plane, game->player.y_plane);
}

int is_valid_pos(t_game* game, double new_x, double new_y)
{
    return (game->map[(int)new_y][(int)new_x] == '#');
}

void move(t_game* game, double x_dir, double y_dir, double speed)
{
    double new_x = game->player.x_pos + x_dir * speed;
    double new_y = game->player.y_pos + y_dir * speed;
    if (is_valid_pos(game, new_x, game->player.y_pos))
        game->player.x_pos = new_x;
    if (is_valid_pos(game, game->player.x_pos, new_y))
        game->player.y_pos = new_y;
}


//rotates both player's dir and plane dir(perpendicular to player)
void rotate(t_game* game, double rot_rad)
{
    rotate_vector(&game->player.x_dir, &game->player.y_dir, rot_rad);
    rotate_vector(&game->player.x_plane, &game->player.y_plane, rot_rad);
}

void reset_img(t_game *game)
{
    //mlx_image_to_window(game->mlx, game->img, 0, 0);
    memset(game->img->pixels, 0, game->img->width * game->img->height * sizeof(int32_t));
}


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
    (void)i;
    (void)game;
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
    (void)i;
    (void)game;
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

void    draw_hook(void *param)
{
    t_game *game = (t_game *)param;
    t_raycast r;
    int i;
    int draw_start;
    int draw_end;

    reset_img(game);
    i = 0;
    while (i < game->width)
    {
        ft_memset(&r, 0, sizeof(t_raycast));
        calc_ray_dir(&r, i, game);
        calc_delt_dist(&r, i, game);
        get_step_dir(&r, i, game);
        dda(&r, game);
        calc_perpendicular_dist(&r);
        calculate_wall_position(game, &r, &draw_start, &draw_end);
        draw_wall_strip(game, i, draw_start, draw_end, &r);
        i++;
    }
    draw_map(game);
    draw_player(game, game->map_offset_x + game->player.x_pos *game->scale - 6, game->map_offset_y + game->player.y_pos * game->scale - 6, 12, 0x000000FF);
    draw_player(game, game->map_offset_x + game->player.x_pos *game->scale - 4, game->map_offset_y + game->player.y_pos * game->scale - 4, 8, 0xFFFFFFFF);
}

void player_hook(void* param)
{
    t_game* game = (t_game*)param;
    const double move_speed = 0.1;
    const double rot_speed = 0.05;
    if (game->keys.w)
        move(game, game->player.x_dir, game->player.y_dir, move_speed);
    if (game->keys.s)
        move(game, -game->player.x_dir, -game->player.y_dir, move_speed);
    if (game->keys.a)
        move(game, game->player.y_dir, -game->player.x_dir, move_speed);
    if (game->keys.d)
        move(game, -game->player.y_dir, game->player.x_dir, move_speed);
    if (game->keys.left)
        rotate(game, -rot_speed);
    if (game->keys.right)
        rotate(game, rot_speed);
}

void set_player(t_game* game)
{
    game->player.x_pos += 0.5;
    game->player.y_pos += 0.5;
    game->player.x_dir = 0;
    game->player.y_dir = -1;
    game->player.x_plane = 0.66;
    if (game->player.orientation == 'E')
        rotate(game, PI / 2);
    else if (game->player.orientation == 'S')
        rotate(game, PI);
    else if (game->player.orientation == 'W')
        rotate(game, -PI / 2);
}
void init(t_game *game)
{
    set_player(game);

    if (game->map_width > game->map_height)
        game->scale = 400 / game->map_width;
    else
        game->scale = 400 / game->map_height;
    game->width = 1600;
    game->height = 1000;
    game->map_offset_x = 1600 - game->map_width * game->scale - game->scale;
    game->map_offset_y = game->scale;
    ft_memset(&game->keys, 0, sizeof(t_keys));
}

int render(t_game *game)
{
    init(game);

    game->mlx = mlx_init(game->width, game->height, "cub3D", 0);
    game->img = mlx_new_image(game->mlx, game->width, game->height);
    game->textures.vigne = mlx_texture_to_image(game->mlx, game->textures.vignette);
    mlx_resize_image(game->textures.vigne,  game->width , game->height);

    mlx_image_to_window(game->mlx, game->img, 0, 0);
    mlx_image_to_window(game->mlx, game->textures.vigne, 0, 0);
    mlx_loop_hook(game->mlx, player_hook, game);
    mlx_loop_hook(game->mlx, draw_hook, game);

    mlx_key_hook(game->mlx, key_hook, game);
    
    mlx_loop(game->mlx);
    
    return 0;
}
