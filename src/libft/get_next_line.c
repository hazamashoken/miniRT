/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 10:20:53 by abossel           #+#    #+#             */
/*   Updated: 2022/10/08 11:39:03 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

#define GNL_BUFFER_SIZE 512

static char	*join_line(char *line, char *buffer)
{
	char	*join;

	if (line == NULL)
		return (ft_strdup(buffer));
	join = ft_strjoin(line, buffer);
	free(line);
	return (join);
}

static int	read_one(int fd, char *buffer)
{
	int	num;

	num = read(fd, buffer, 1);
	if (num <= 0)
		buffer[0] = '\0';
	else
		buffer[1] = '\0';
	return (num);
}

char	*get_next_line(int fd)
{
	char	buffer[GNL_BUFFER_SIZE];
	char	*line;
	int		num;
	int		pos;

	if (fd < 0)
		return (NULL);
	pos = 0;
	num = read_one(fd, buffer);
	if (num <= 0)
		return (NULL);
	line = NULL;
	while (num > 0 && buffer[pos] != '\n')
	{
		pos++;
		if (pos == GNL_BUFFER_SIZE - 1)
		{
			line = join_line(line, buffer);
			pos = 0;
		}
		num = read_one(fd, &buffer[pos]);
	}
	return (join_line(line, buffer));
}
