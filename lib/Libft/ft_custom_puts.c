/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_custom_puts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 16:18:00 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/05 16:18:35 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	custom_puts(const char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (write(STDOUT_FILENO, str, 1) == -1)
			return (-1);
		str++;
		count++;
	}
	if (write(STDOUT_FILENO, "\n", 1) == -1)
		return (-1);
	return (count + 1);
}
