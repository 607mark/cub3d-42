#include "../../inc/cub3d.h"

int is_valid_pos(t_game* game, double new_x, double new_y)
{
    return (game->map[(int)new_y][(int)new_x] == '#');
}

void    draw_hook(void *param)
{
    t_game *game = (t_game *)param;
    t_raycast r;
    int i;
    int draw_start;
    int draw_end;

    ft_memset(game->img->pixels, 0, game->img->width * game->img->height * sizeof(int32_t));
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
    game->width = 2040;
    game->height = 1000;
    game->map_offset_x = game->width - game->map_width * game->scale - game->scale;
    game->map_offset_y = game->scale;
    ft_memset(&game->keys, 0, sizeof(t_keys));
    game->mlx = mlx_init(game->width, game->height, "cub3D", 0);
    game->img = mlx_new_image(game->mlx, game->width, game->height);
    game->textures.vigne = mlx_texture_to_image(game->mlx, game->textures.vignette);
    mlx_resize_image(game->textures.vigne,  game->width , game->height);
    mlx_image_to_window(game->mlx, game->img, 0, 0);
    mlx_image_to_window(game->mlx, game->textures.vigne, 0, 0);
}

int render(t_game *game)
{
    init(game);
    mlx_loop_hook(game->mlx, player_hook, game);
    mlx_loop_hook(game->mlx, draw_hook, game);
    mlx_key_hook(game->mlx, key_hook, game);
    mlx_loop(game->mlx);
    
    return 0;
}
