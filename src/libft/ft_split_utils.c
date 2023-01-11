/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:43:42 by abossel           #+#    #+#             */
/*   Updated: 2022/10/03 11:35:19 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_split_free(char **words)
{
	int	i;

	if (words != NULL)
	{
		i = 0;
		while (words[i] != NULL)
		{
			free(words[i]);
			i++;
		}
		free(words);
	}
}

int	ft_split_size(char **words)
{
	int	i;

	i = 0;
	if (words != NULL)
	{
		while (words[i] != NULL)
		{
			i++;
		}
	}
	return (i);
}

char	**ft_split_dup(char **words)
{
	char	**dup;
	int		size;
	int		i;

	if (words == NULL)
		return (NULL);
	size = ft_split_size(words);
	dup = malloc(sizeof(char **) * (size + 1));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		dup[i] = ft_strdup(words[i]);
		if (dup[i] == NULL)
		{
			ft_split_free(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	ft_split_delfront(char **words)
{
	int	i;

	i = 0;
	if (words != NULL)
	{
		if (words[0] != NULL)
			free(words[0]);
		while (words[i] != NULL)
		{
			words[i] = words[i + 1];
			i++;
		}
	}
}

void	ft_split_delback(char **words)
{
	int	i;

	i = 0;
	if (words != NULL)
	{
		if (words[0] == NULL)
			return ;
		while (words[i] != NULL)
		{
			i++;
		}
		free(words[i - 1]);
		words[i - 1] = NULL;
	}
}
