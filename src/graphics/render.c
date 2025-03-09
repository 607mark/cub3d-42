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
void set_game( t_game *game)
{
    game->ceiling_rgb = 11111111;
    game->floor_rgb = 19999999;
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
void draw_game(t_game *game)
{
    draw_ceiling(game);
    draw_floor(game);
    mlx_image_to_window(game->win.mlx, game->img, 0, 0);
}

int main()
{
    t_game game;
    ft_memset(&game, sizeof(game), 0);
    set_game(&game);
    init_win(&game);
    draw_game(&game);
    mlx_close_hook(game.win.mlx, close_window, &game);
	mlx_key_hook(game.win.mlx, keyhook, &game);
	mlx_loop(game.win.mlx);
}


