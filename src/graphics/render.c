
// void draw_ceiling(t_game *game)
// {
//         int i;
//         int j;

//         j = -1;
//         while (++j <= HEIGHT / 2)
//         {
//             i = -1;
//             while (++i < WIDTH)
//                 mlx_put_pixel(game->img, i, j, game->ceiling_rgb);
//         }
// }

// void draw_floor(t_game *game)
// {
//     int i;
//     int j;

//     j =  HEIGHT / 2;
//     while (++j < HEIGHT)
//     {
//         i = -1;
//         while (++i < WIDTH)
//             mlx_put_pixel(game->img, i, j, game->floor_rgb);
//     }
// }

#include "../../inc/cub3d.h"


// #define MAP_WIDTH 10
// #define MAP_HEIGHT 10
// #define SCREEN_WIDTH 1000
// #define SCREEN_HEIGHT 1000



// int map[MAP_HEIGHT][MAP_WIDTH] = {
//     {1,1,1,1,1,1,1,1,1,1},
//     {1,0,0,1,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,1,1,1,0,0,1},
//     {1,0,0,0,0,0,0,0,1,1},
//     {1,0,0,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,1,0,0,1},
//     {1,1,1,1,1,1,1,1,1,1}
// };

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
    printf("MOVE\n");
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

//draws square of given color and size
void draw_square(t_game *game, int x, int y, int size, uint32_t color)
{
    int start_x = x;
    int start_y = y;
    int end_x = x + size - 1;
    int end_y = y + size - 1;
    int draw_y = start_y;
    while (draw_y <= end_y)
    {
        int draw_x = start_x;
        while (draw_x <= end_x)
        {
            if(size == game->scale && (!(draw_x % game->scale) || !(draw_y % game->scale)))
                mlx_put_pixel(game->img, draw_x, draw_y, 0x000000FF);
            else
                mlx_put_pixel(game->img, draw_x, draw_y, color);
            draw_x++;
        }
        draw_y++;
    }
}


//draws simple visualization of top-down view map 
void draw_map(t_game* game)
{
    memset(game->img->pixels, 0, game->map_width * game->scale * game->map_height * game->scale * sizeof(uint32_t));
    int i, j;
    i = 0;
    while(i < game->map_width)
    {
        j = 0;
        while(j < game->map_height)
        {
            if (game->map[j][i] == '1')
                draw_square(game, i * game->scale, j * game->scale, game->scale, 0xF000002F);
            j++;
        }
        i++;
    }
}
//bresenham that draws from player to player's direction the line of specific length
void draw_line(t_game *game, double xdir, double ydir, double line_length, uint32_t color)
{
    uint32_t start_x = game->player.x_pos * game->scale;
    uint32_t start_y = game->player.y_pos * game->scale;
    double end_x = start_x + xdir * line_length;
    double end_y = start_y + ydir * line_length;
    int x0 = start_x;
    int y0 = start_y;
    int x1 = end_x;
    int y1 = end_y;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (42)
    {
            
        if (x0 >= 0 && x0 < game->width && y0 - 1>= 0 && y0 + 1 < game->height)
        {
            mlx_put_pixel(game->img, x0, y0, color);
            mlx_put_pixel(game->img, x0 , y0 + 1, color);
            mlx_put_pixel(game->img, x0, y0 -1, color);
        }
        draw_square(game, start_x - 5, start_y -5, 10, 0xFFFFFFFF);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
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

// void render_hook(void* param)
// {
//     t_game *game = (t_game *) param;
//     t_raycast r;
//     ft_memset(&r, 0, sizeof(t_raycast));
//     //reset_img(game);
//     int i = 0;
//     while(i < SCREEN_WIDTH)
//     {
//         calc_ray_dir(&r, i, game);
//         calc_delt_dist(&r, i, game);
//         get_step_dir(&r, i, game);
//         draw_line(game, r.x_raydir, r.y_raydir, 66, 0x5F40FF80);
//         dda(&r, game);
//         if (r.side == 0)
//             r.perp_dist = (r.x_side_dist - r.x_delt_dist);
//         else
//             r.perp_dist = (r.y_side_dist - r.y_delt_dist);
          
//         i++;
//     }
// }

void draw_ray(t_game *game, t_raycast *r)
{
    double hit_x, hit_y;
    
    hit_x = game->player.x_pos + r->x_raydir * r->perp_dist;
    hit_y = game->player.y_pos + r->y_raydir * r->perp_dist;
    uint32_t hit_x_screen = (uint32_t)(hit_x * game->scale);
    uint32_t hit_y_screen = (uint32_t)(hit_y * game->scale);

    int x0 = game->player.x_pos * game->scale;
    int y0 = game->player.y_pos * game->scale;
    int x1 = hit_x_screen;
    int y1 = hit_y_screen;

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (42)
    {
        if (x0 >= 0 && x0 < game->width && y0 >= 0 && y0 < game->height)
            mlx_put_pixel(game->img, x0, y0, 0x9F4000F0);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}
// void draw_hook(void* param)
// {
//     t_game* game = (t_game*)param;
//     t_raycast r;

//     draw_map(game);
//     int i = 0;
//     while (i < game->width) {
//         ft_memset(&r, 0, sizeof(t_raycast));
//         calc_ray_dir(&r, i, game);
//         calc_delt_dist(&r, i, game);
//         get_step_dir(&r, i, game);
//         dda(&r, game);
//         calc_perpendicular_dist(&r);
//         draw_ray(game, &r);

//         i += 10;
//     }
//     draw_square(game, game->player.x_pos *game->scale - 5, game->player.y_pos * game->scale - 5, 10, 0xFFFFFFFF);
//     draw_line(game, game->player.x_dir, game->player.y_dir, 90, 0xFFFFFFFF);
// }

void    draw_hook(void *param)
{
    t_game *game = (t_game *)param;
    t_raycast r;
    int i;
    int draw_start;
    int draw_end;

    memset(game->img->pixels, 0, game->width * game->height * sizeof(uint32_t));
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
}

void player_hook(void* param)
{
    t_game* game = (t_game*)param;
    const double move_speed = 0.1;
    const double rot_speed = 0.05;
    printf("%f\n", game->player.x_pos);
    printf("%f\n", game->player.y_pos);
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

void init(t_game *game)
{
    game->player.x_pos += 0.5;
    game->player.y_pos += 0.5;
    game->player.x_dir = 0;
    game->player.y_dir = -1;
    game->player.x_plane = 0.66;
    game->scale = 70;
    game->width = game->map_width * game->scale;
    game->height = game->map_height * game->scale;
    // rotate_vector(&game->player.x_dir, &game->player.y_dir, 3.14 / 2);
    // rotate_vector(&game->player.x_plane, &game->player.y_plane, 3.14 / 2);
    
    
    game->keys.w = 0;
    game->keys.a = 0;
    game->keys.s = 0;
    game->keys.d = 0;
    game->keys.left = 0;
    game->keys.right = 0;
}

int render(t_game *game) {


       

    // Print key mappings

    init(game);

    game->mlx = mlx_init(game->width, game->height, "cub3D", 0);
    game->img = mlx_new_image(game->mlx, game->width, game->height);
    // validate_map(game);

    mlx_image_to_window(game->mlx, game->img, 0, 0);
    mlx_loop_hook(game->mlx, player_hook, game);
    mlx_loop_hook(game->mlx, draw_hook, game);
    // // // mlx_loop_hook(game.mlx, render_hook, &game);
    // // //mlx_loop_hook(game.mlx, print_hook, &game);
    mlx_key_hook(game->mlx, key_hook, game);
    
    mlx_loop(game->mlx);
    
    // mlx_delete_image(game->mlx, game->img);
    // mlx_terminate(game->mlx);
    
    return 0;
}
