/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:09:06 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/27 13:55:49 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	skip_spaces(char **ptr)
{
	if (ptr && *ptr)
	{
		while (ft_isspace(**ptr))
			(*ptr)++;
	}
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
	if (end_char == ',')
		*ptr = endptr + 1;
	else
		*ptr = endptr;
	return (value);
}

void	parse_color(int *color, char *line, t_game *game)
{
	char	*ptr;
	t_rgb	rgb;
	int		err_flag;

	ptr = line + 2;
	err_flag = 0;
	skip_spaces(&ptr);
	rgb.r = parse_component(&ptr, ',', &err_flag);
	if (rgb.r == -1)
	{
		free(line);
		error_exit("Invalid RGB format: RED component", game);
	}
	skip_spaces(&ptr);
	rgb.g = parse_component(&ptr, ',', &err_flag);
	if (rgb.g == -1)
	{
		free(line);
		error_exit("Invalid RGB format: GREEN component", game);
	}
	skip_spaces(&ptr);
	rgb.b = parse_component(&ptr, '\0', &err_flag);
	if (rgb.b == -1)
	{
		free(line);
		error_exit("Invalid RGB format: BLUE or duplicate", game);
	}
	skip_spaces(&ptr);
	if (*ptr != '\0')
	{
		free(line);
		error_exit("Invalid RGB format: trailing characters", game);
	}
	free(line);
	*color = (uint32_t)((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}
