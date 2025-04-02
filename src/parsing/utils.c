/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhakimu <rkhakimu@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 10:07:26 by rkhakimu          #+#    #+#             */
/*   Updated: 2025/04/02 10:34:27 by rkhakimu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	skip_spaces(char **ptr)
{
	if (ptr && *ptr)
	{
		while (ft_isspace(**ptr))
			(*ptr)++;
	}
}

int	is_newline(char *line)
{
	int	i;
	int	len;

	if (!line)
		return (0);
	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (1);
	len = ft_strlen(line);
	i = 0;
	while (i < len - 1)
	{
		if (ft_isspace((int)line[i]))
		{
			i++;
			continue ;
		}
		else
			break ;
	}
	if (line[i] == '\n')
		return (1);
	if (i == len)
		return (1);
	return (0);
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

int	validate_tex_ext(char *filename, t_game *game)
{
	char	*ext;

	ext = NULL;
	ext = ft_strrchr(filename, '.');
	if (!ext)
		return (0);
	if (ft_strcmp(".png", ext) == 0)
		return (1);
	if (ft_strcmp(".xpm", ext) == 0)
		error_exit("warning: .xpm detected. Needs to be .png", game);
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
