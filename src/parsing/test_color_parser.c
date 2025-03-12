# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include "../../lib/Libft/libft.h"

void	error_exit(char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit (1);
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
	if (*color == -1 /* || (*color != -1 && *color != 0) */)
		error_exit("Invalid RGB format: BLUE or duplicate");
	skip_spaces(&ptr);
	if (*ptr != '\0')
		error_exit("Invalid RGB format: trailing characters");
	*color = (r << 16) | (g << 8) | *color;
}

void test_parse_color_valid_rgb_format(void)
{
    char *line = "F 255";
    int color = 0;

    parse_color(&color, line);

    int expected = (255 << 16) | (128 << 8) | 64;
    if (color == expected)
        printf("test_parse_color_valid_rgb_format: PASSED\n");
    else
        printf("test_parse_color_valid_rgb_format: FAILED (Expected: 0x%06X, Got: 0x%06X)\n", expected, color);
}

int main(void)
{
    test_parse_color_valid_rgb_format();
    return 0;
}
