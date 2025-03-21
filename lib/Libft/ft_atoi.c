/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:42:47 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/06 09:58:14 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	process_digits(const char *str, long long n, int sign)
{
	long long	result;

	while (*str >= '0' && *str <= '9')
	{
		if (n > LONG_MAX / 10)
		{
			if (sign > 0)
				return (-1);
			return (0);
		}
		result = n * 10;
		if (result > LONG_MAX - (*str - '0'))
		{
			if (sign > 0)
				return (-1);
			return (0);
		}
		n = result + (*str - '0');
		str++;
	}
	return ((int)(sign * n));
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	n;

	sign = 1;
	n = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	return (process_digits(str, n, sign));
}
