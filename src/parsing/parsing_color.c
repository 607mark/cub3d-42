/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:09:06 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/04/02 12:03:22 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
	while (ft_isdigit(*endptr))
		endptr++;
	if (*endptr != end_char || value < 0 || value > 255 || *err_flag)
		return (-1);
	if (end_char == ',')
		*ptr = endptr + 1;
	else
		*ptr = endptr;
	return (value);
}

int	parse_rgb_component(char **ptr, char delimiter, t_game *game, char *line)
{
	int	component;
	int	err_flag;

	err_flag = 0;
	skip_spaces(ptr);
	component = parse_component(ptr, delimiter, &err_flag);
	if (component == -1)
	{
		free(line);
		if (delimiter == ',')
			error_exit("Invalid RGB format", game);
		else
			error_exit("Invalid RGB format", game);
	}
	return (component);
}

void	parse_color(int *color, char *line, t_game *game)
{
	char	*ptr;
	t_rgb	rgb;
	int		color_type;

	if (!line)
		error_exit("Null line pointer", game);
	color_type = check_color_duplicate(line, game);
	ptr = line + 2;
	rgb.r = parse_rgb_component(&ptr, ',', game, line);
	rgb.g = parse_rgb_component(&ptr, ',', game, line);
	rgb.b = parse_rgb_component(&ptr, '\0', game, line);
	skip_spaces(&ptr);
	if (*ptr != '\0')
	{
		free(line);
		line = NULL;
		error_exit("Invalid RGB format", game);
	}
	*color = (uint32_t)((rgb.r << 16) | (rgb.g << 8) | rgb.b);
	if (color_type == 1)
		game->floor_rgb = *color;
	else if (color_type == 2)
		game->ceiling_rgb = *color;
	if (line)
		free(line);
}
