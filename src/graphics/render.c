
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
#define SCREEN_HEIGHT 500

int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,1},
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

void key_hook(mlx_key_data_t keygame, void* param)
{
    t_game* game = (t_game*)param;
    
    if (keygame.key == MLX_KEY_W)
        game->keys.w_press = (keygame.action != MLX_RELEASE);
    if (keygame.key == MLX_KEY_S)
        game->keys.s_press = (keygame.action != MLX_RELEASE);
    if (keygame.key == MLX_KEY_A)
        game->keys.a_press = (keygame.action != MLX_RELEASE);
    if (keygame.key == MLX_KEY_D)
        game->keys.d_press = (keygame.action != MLX_RELEASE);
    if (keygame.key == MLX_KEY_LEFT)
        game->keys.left_press = (keygame.action != MLX_RELEASE);
    if (keygame.key == MLX_KEY_RIGHT)
        game->keys.right_press = (keygame.action != MLX_RELEASE);
    if (keygame.key == MLX_KEY_ESCAPE && keygame.action == MLX_PRESS)
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

void move(t_game* game, double dir_x, double dir_y, double speed)
{
    double new_x = game->player.x_pos + dir_x * speed;
    double new_y = game->player.y_pos + dir_y * speed;
    
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

void player_hook(void* param)
{
    t_game* game = (t_game*)param;
    const double move_speed = 0.1;
    const double rot_speed = 0.01;

    if (game->keys.w_press)
        move(game, game->player.x_dir, game->player.y_dir, move_speed);
    if (game->keys.s_press)
        move(game, -game->player.x_dir, -game->player.y_dir, move_speed);
    if (game->keys.a_press)
        move(game, game->player.y_dir, -game->player.x_dir, move_speed);
    if (game->keys.d_press)
        move(game, -game->player.y_dir, game->player.x_dir, move_speed);
    if (game->keys.left_press)
        rotate(game, rot_speed);
    if (game->keys.right_press)
        rotate(game, -rot_speed);
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
    

    game->keys.w_press = 0;
    game->keys.a_press = 0;
    game->keys.s_press = 0;
    game->keys.d_press = 0;
    game->keys.left_press = 0;
    game->keys.right_press = 0;
}

int main(void) {
    t_game game;
    
    game.mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D", 0);
    game.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);

    init(&game);
    mlx_loop_hook(game.mlx, player_hook, &game);
    mlx_loop_hook(game.mlx, print_hook, &game);
    mlx_key_hook(game.mlx, key_hook, &game);
    
    mlx_loop(game.mlx);
    
    mlx_delete_image(game.mlx, game.img);
    mlx_terminate(game.mlx);
    
    return 0;
}