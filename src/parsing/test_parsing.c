# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include "../../lib/Libft/libft.h"

typedef struct	s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	char		orientation;
}	t_player;

typedef struct	s_texture
{
	char		*north;
	char		*south;
	char		*east;
	char		*west;
}	t_texture;

typedef struct	s_game
{
	char		**map;
	int			map_width;
	int			map_height;
	t_player	player;
	t_texture	textures;
	int			floor_rgb;
	int			ceiling_rgb;
}	t_game;


/*Errors*/
void	error_exit(char *msg);
void	free_game(t_game *game);



/* Parsing functions */
void	parse_cub_file(t_game *game, char *filename);
void	error_exit(char *msg);
int		validate_file_ext(char *filename);
int		validate_file_access(char *filename);
int		is_config_element(char *line);
void	init_game(t_game *game);
void	parse_texture(t_texture *textures, char *line);
void	parse_color(int *color, char *line);

/* MAP */
void	read_map(t_game *game, int fd);
void	validate_map(t_game *game);
char	**ft_realloc_2d(char **old, int new_size);
void	check_row(char *row, int y, t_game *game, int *player_found);
void	flood_fill(t_game *game, int x, int y, char **map);

void	flood_fill(t_game *game, int x, int y, char **map)
{
	if (x < 0 || x >= game->map_width || y < 0 || y >= game->map_height)
		error_exit("Map not enclosed by walls");
	if (map[y][x] == '1' || map[y][x] == '#')
		return ;
	if (ft_isspace(map[y][x]))
		return ;
	map[y][x] = '#';
	flood_fill(game, x + 1, y, map);
	flood_fill(game, x - 1, y, map);
	flood_fill(game, x, y + 1, map);
	flood_fill(game, x, y - 1, map);
}

void	parse_cub_file(t_game *game, char *filename)
{
	int		fd;
	char	*line;
	
	if (!validate_file_ext(filename) || !validate_file_access(filename))
		error_exit("Invalid file extension or access");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file");
	init_game(game);
	line = get_next_line(fd);
	while (line && is_config_element(line))
	{
		read_config_line(game, line);
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		error_exit("No map found in file");
	read_map(game, fd);
	close(fd);
	if (!game->textures.north || !game->textures.south
		|| game->textures.west || !game->textures.east
		|| game->floor_rgb == -1 || game->ceiling_rgb == -1)
		error_exit("Missing config elements");
	validate_map(game);
}

void	read_config_line(t_game *game, char *line)
{
	char	*trimmed;
	
	trimmed = ft_strtrim(line, " \t\n");
	if (!trimmed)
		error_exit("Memory allocation failed");
	if (ft_strcmp(trimmed, "NO ", 3) == 0)
		parse_texture(&game->textures, trimmed);
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		parse_texture(&game->textures, trimmed);
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		parse_texture(&game->textures, trimmed);
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		parse_texture(&game->textures, trimmed);
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
		parse_color(&game->floor_rgb, trimmed);
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		parse_color(&game->ceiling_rgb, trimmed);
	else
		error_exit("invalid config line");
	free(trimmed);
}

void	parse_texture(t_texture *textures, char *line)
{
	char	*path;
	char	*start;

	start = line + 3;
	while (ft_isspace(*start))
		start++;
	path = ft_strdup(start);
	if (!path)
		error_exit("Memory allocation failed");
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (textures->north)
			error_exit("Duplicate NO textrure");
		textures->north = path;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (textures->south)
			error_exit("Duplicate SO textrure");
		textures->south = path;
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (textures->west)
			error_exit("Duplicate WE textrure");
		textures->west = path;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (textures->east)
			error_exit("Duplicate EA textrure");
		textures->east = path;
	}
}
static char	**copy_rows(char **new, char **old, int index, int numofrows)
{
	if (index >= numofrows)
		return (new);
	new[index] = old[index];
	return (copy_rows(new, old, index + 1, numofrows));
}

char	**ft_realloc_2d(char **old, int new_size)
{
	char	**new;

	new = malloc(new_size * sizeof(char *));
	if (!new)
		return (NULL);
	if (old)
	{
		new = copy_rows(new, old, 0, new_size - 1);
		free(old);
	}
	return (new);
}

void	read_map(t_game *game, int fd)
{
	char	*line;
	char	**temp_map;
	int		height;

	temp_map = NULL;
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		temp_map = ft_realloc_2d(temp_map, height + 1);
		if (!temp_map)
			error_exit("Memory allocation failed");
		temp_map[height] = ft_strdup(line);
		if (!temp_map[height])
			error_exit("Memory allocation failed");
		free(line);
		height++;
		line = get_next_line(fd);
	}
	if (height == 0)
		error_exit("Empty map");
	game->map = temp_map;
	game->map_height = height;
}

void	check_row(char *row, int y, t_game *game, int *player_found)
{
	char	*ptr;
	
	ptr = row;
	while(*ptr)
	{
		if (*ptr == 'N' || *ptr == 'S' || *ptr == 'W' || *ptr == 'E')
		{
			if (*player_found)
				error_exit("Multiple players in map");
			*player_found = 1;
			game->player.x = ptr - row;
			game->player.y = y;
			game->player.orientation = *ptr;
		}
		else if (*ptr != '0' && *ptr != '1' && !ft_isspace(*ptr))
			error_exit("Invalid character in map");
		ptr++;
	}
}

int	validate_file_ext(char *filename)
{
	char	*ext;
	
	ext = NULL;
	ext = ft_strrchr(filename, '.');
	if (!ext)
		return (0);
	if (ft_strcmp(".cub", ext) == 0)
		return (1);
	return (0);
}

int	validate_file_access(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	is_config_element(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
			ft_strncmp(line, "WE ", 3) ==0 || ft_strncmp(line, "EA ", 3) == 0 ||
			ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

void	validate_map(t_game *game)
{
	int	y;
	int	player_found;
	
	y = 0;
	player_found = 0;
	while (y < game->map_height)
	{
		check_row(game->map[y], y, game, &player_found);
		if (ft_strlen(game->map[y]) > game->map_width)
			game->map_width = ft_strlen(game->map[y]);
		y++;
	}
	if (!player_found)
		error_exit("No player found in map");
	flood_fill(game, game->player.x, game->player.y, game->map);
}

static void	skip_spaces(char **ptr)
{
	while (ft_isspace(**ptr))
	(*ptr)++;
}

static int	check_start(char *ptr)
{
	if (*ptr == '-' || *ptr == '+')
		return (0);
	if (!ft_isdigit(*ptr))
		return (0);
	return (1);
}

static int	count_digits(char *ptr, int *err_flag)
{
	int	digit_count;
	
	digit_count = 0;
	while (ft_isdigit(*ptr))
	{
		digit_count++;
		if (digit_count > 3)
			*err_flag = 1;
		ptr++;
	}
	return (digit_count);
}

static int	parse_component(char **ptr, char end_char, int *err_flag)
{
	int		value;
	char	*endptr;

	if (!check_start(*ptr))
		return (-1);
	value = ft_atoi(*ptr);
	endptr = *ptr;
	count_digits(endptr, err_flag);
	while(ft_isdigit(*endptr))
		endptr++;
	if (*endptr != end_char || value < 0 || value > 255 || *err_flag)
		return (-1);
	*ptr = endptr + 1;
	return (value);
}

void	parse_color(int *color, char *line)
{
	char	*ptr;
	int		r;
	int		g;
	int		err_flag;

	ptr = line + 2;
	err_flag = 0;
	skip_spaces(&ptr);
	r = parse_component(&ptr, ',', &err_flag);
	if (r == -1)
		error_exit("Invalid RGB format: RED component");
	skip_spaces(&ptr);
	g = parse_component(&ptr, ',', &err_flag);
	if (g == -1)
		error_exit("Invalid RGB format: GREEN component");
	skip_spaces(&ptr);
	*color = parse_component(&ptr, '\0', &err_flag);
	if (*color == -1 || (*color != -1 && *color != 0))
		error_exit("Invalid RGB format: BLUE or duplicate");
	skip_spaces(&ptr);
	if (*ptr != '\0')
		error_exit("Invalid RGB format: trailing characters");
	*color = (r << 16) | (g << 8) | *color;
}

