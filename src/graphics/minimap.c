#include "../../inc/cub3d.h"

void draw_player(t_game *game, int x, int y, int size, uint32_t color)
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
                mlx_put_pixel(game->img, draw_x, draw_y, color);
            draw_x++;
        }
        draw_y++;
    }
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
                mlx_put_pixel(game->img, draw_x, draw_y, color);
            draw_x++;
        }
        draw_y++;
    }
    start_x = x;
    start_y = end_y + 1;
    end_x = start_x + size -1;
    end_y = start_y + size / 3;
    draw_y = start_y;
    while (draw_y <= end_y)
    {
        int draw_x = start_x;
        while (draw_x <= end_x)
        {
            mlx_put_pixel(game->img, draw_x, draw_y, 0x470D00FF);
            draw_x++;
        }
        draw_y++;
    }
}

void draw_background(t_game *game, int x, int y, uint32_t color)
{
    int start_x = x;
    int start_y = y;
    int end_x = x + game->map_width * game->scale - 1;
    int end_y = y + game->map_height * game->scale + game->scale / 3 - 1;
    int draw_y = start_y;
    while (draw_y <= end_y)
    {
        int draw_x = start_x;
        while (draw_x <= end_x)
        {
                mlx_put_pixel(game->img, draw_x, draw_y, color);
            draw_x++;
        }
        draw_y++;
    }
}
//draws simple visualization of top-down view map 
void draw_map(t_game* game)
{
    draw_background(game, game->map_offset_x, game->map_offset_y , 0xD6C0ABFF);
    // memset(game->img->pixels, 0, game->map_width * game->scale * game->map_height * game->scale * sizeof(uint32_t));
    int i, j;
    i = 0;
    while(i < game->map_width)
    {
        j = 0;
        while(j < game->map_height)
        {
            if (game->map[j][i] == '1')
                draw_square(game, game->map_offset_x + i * game->scale, game->map_offset_y + j * game->scale, game->scale, 0xF000002F);
            // else if (game->map[j][i] == '#')
            //     draw_square(game, game->map_offset_x + i * game->scale, game->map_offset_y + j * game->scale, game->scale, 0x990000FF);
            j++;
        }
        i++;
    }
}