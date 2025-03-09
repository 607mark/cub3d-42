#include "../inc/cub3d.h"

void	clean_exit(t_game *game, const char *s)
{
    game = game;
    printf("%s\n", s);
}

static void	close_window(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	clean_exit(game, "Window was closed.");
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
    keydata = keydata;
	game = (t_game *)param;
}
void	init_win(t_game *game)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 0);
	game->win.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", 1);
	if (!game->win.mlx)
		clean_exit(game, "Failed to mlx_init.");
    game->img = mlx_new_image(game->win.mlx, WIDTH, HEIGHT);
    memset(game->img->pixels, 255, WIDTH * HEIGHT * sizeof(int32_t));

}

void rotation_matrix(double* x, double* y, double angle) {
    double old_x = *x;
    double cos_angle = cos(angle);
    double sin_angle = sin(angle);
    *x = old_x * cos_angle - *y * sin_angle;
    *y = old_x * sin_angle + *y * cos_angle;
}
void set_game( t_game *game)
{
    game->ceiling_rgb = 11111111;
    game->floor_rgb = 19999999;

    game->player.x = 3.5;
    game->player.y = 2.5;
    game->player.dir_x = 1.0;
    game->player.dir_y = 0.0;
    game->player.plane_x = 0.0;
    game->player.plane_y = 0.66;
}
void draw_ceiling(t_game *game)
{
    int i;
    int j;

    j = -1;
    while (++j <= HEIGHT / 2)
    {
        i = -1;
        while (++i < WIDTH)
            mlx_put_pixel(game->img, i, j, game->ceiling_rgb);
    }
}
void draw_floor(t_game *game)
{
    int i;
    int j;

    j =  HEIGHT / 2;
    while (++j < HEIGHT)
    {
        i = -1;
        while (++i < WIDTH)
            mlx_put_pixel(game->img, i, j, game->floor_rgb);
    }
}

void clean_image(t_game *game)
{
    mlx_image_to_window(game->win.mlx, game->img, 0, 0);
    ft_memset(game->img->pixels, 0, game->img->width * game->img->height * sizeof(int32_t));
}
void draw_game(t_game *game)
{
    clean_image(game);
    draw_ceiling(game);
    draw_floor(game);
    
}

int main()
{
    t_game game;

    ft_memset(&game, sizeof(game), 0);
    int map[10][10] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,1,0,0,0,0,1},
        {1,0,1,0,0,0,1,0,0,1},
        {1,0,1,1,0,1,0,0,0,1},
        {1,0,0,0,0,0,0,1,0,1},
        {1,1,0,1,0,1,1,1,1,1},
        {1,0,0,0,0,0,1,0,1,1},
        {1,0,1,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    };
    game.map = &map;
    
    set_game(&game);
    init_win(&game);
    draw_game(&game);
    mlx_close_hook(game.win.mlx, close_window, &game);
	mlx_key_hook(game.win.mlx, keyhook, &game);
	mlx_loop(game.win.mlx);
}


