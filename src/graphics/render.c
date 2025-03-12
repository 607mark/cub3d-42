
// void draw_ceiling(t_game *game)
// {
    //     int i;
    //     int j;

    //     j = -1;
    //     while (++j <= HEIGHT / 2)
    //     {
    //         i = -1;
    //         while (++i < WIDTH)
    //             mlx_put_pixel(game->img, i, j, game->ceiling_rgb);
    //     }
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


#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,0,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,1},
    {1,1,1,1,1,1,1,1,1,1}
};

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
    return (map[(int)new_y][(int)new_x] == 0);
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

void rotate(t_game* game, double rot_rad)
{
    rotate_vector(&game->player.x_dir, &game->player.y_dir, rot_rad);
    rotate_vector(&game->player.x_plane, &game->player.y_plane, rot_rad);
}

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
            if(size ==100 && (!(draw_x % 100) || !(draw_y % 100)))
                mlx_put_pixel(game->img, draw_x, draw_y, 0x000000FF);
            else
                mlx_put_pixel(game->img, draw_x, draw_y, color);
            draw_x++;
        }
        draw_y++;
    }
}

void draw_map(t_game* game)
{
    memset(game->img->pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint32_t));
    int i, j;
    i = 0;
    while(i < 10)
    {
        j = 0;
        while(j < 10)
        {
            if (map[j][i] == 1)
                draw_square(game, i * 100, j * 100, 100, 0xF000002F);
            j++;
        }
        i++;
    }
}

void draw_hook(void* param)
{
    t_game* game = (t_game*)param;
    
    draw_map(game);
    uint32_t start_x = game->player.x_pos * 100;
    uint32_t start_y = game->player.y_pos * 100;
    const double line_length = 90;
    double end_x = start_x + game->player.x_dir * line_length;
    double end_y = start_y + game->player.y_dir * line_length;
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
            
        if (x0 >= 0 && x0 < SCREEN_WIDTH && y0 - 1>= 0 && y0 + 1 < SCREEN_HEIGHT)
        {
            mlx_put_pixel(game->img, x0, y0, 0xFFFFFFFF);
            mlx_put_pixel(game->img, x0 , y0 + 1, 0xFFFFFFFF);
            mlx_put_pixel(game->img, x0, y0 -1, 0xFFFFFFFF);
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

void player_hook(void* param)
{
    t_game* game = (t_game*)param;
    const double move_speed = 0.1;
    const double rot_speed = 0.1;

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
    game->player.x_pos = 1.5;
    game->player.y_pos = 1.5;
    game->player.x_dir = 0;
    game->player.y_dir = -1;
    game->player.x_plane = 0.66;
    game->player.y_plane = 0;
    // rotate_vector(&game->player.x_dir, &game->player.y_dir, 3.14 / 2);
    // rotate_vector(&game->player.x_plane, &game->player.y_plane, 3.14 / 2);
    

    game->keys.w = 0;
    game->keys.a = 0;
    game->keys.s = 0;
    game->keys.d = 0;
    game->keys.left = 0;
    game->keys.right = 0;
}

int main(void) {
    t_game game;
    
    game.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", 0);
    game.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);

    init(&game);
    mlx_image_to_window(game.mlx, game.img, 0, 0);
    mlx_loop_hook(game.mlx, player_hook, &game);
    mlx_loop_hook(game.mlx, draw_hook, &game);
    mlx_loop_hook(game.mlx, print_hook, &game);
    mlx_key_hook(game.mlx, key_hook, &game);
    
    mlx_loop(game.mlx);
    
    mlx_delete_image(game.mlx, game.img);
    mlx_terminate(game.mlx);
    
    return 0;
}
