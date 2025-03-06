/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:59:07 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/03/06 09:52:40 by rkhakimu         ###   ########.fr       */
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

int	validate_file_access(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	rreturn (1);
}
