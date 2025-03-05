/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:59:07 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/05 16:50:17 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
