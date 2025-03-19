/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:09:06 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/19 11:03:47 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
	if (end_char == ',')
		*ptr = endptr + 1;
	else
		*ptr = endptr;
	return (value);
}

void	parse_color(int *color, char *line)
{
	char	*ptr;
	t_rgb	rgb;
	int		err_flag;

	ptr = line + 2;
	err_flag = 0;
	skip_spaces(&ptr);
	rgb.r = parse_component(&ptr, ',', &err_flag);
	if (rgb.r == -1)
		error_exit("Invalid RGB format: RED component");
	skip_spaces(&ptr);
	rgb.g = parse_component(&ptr, ',', &err_flag);
	if (rgb.g == -1)
		error_exit("Invalid RGB format: GREEN component");
	skip_spaces(&ptr);
	rgb.b = parse_component(&ptr, '\0', &err_flag);
	if (rgb.b == -1)
		error_exit("Invalid RGB format: BLUE or duplicate");
	skip_spaces(&ptr);
	while (*ptr == '\n' || ft_isspace(*ptr))
		ptr++;
	if (*ptr != '\0')
		error_exit("Invalid RGB format: trailing characters");
	*color = (uint32_t)((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}
