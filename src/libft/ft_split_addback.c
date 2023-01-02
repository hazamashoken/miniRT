/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_addback.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:07:48 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/06 10:55:36 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_split_size(char	**split)
{
	int	len;

	len = 0;
	while (split[len] != NULL)
		len++;
	return (len);
}

char	**ft_split_addback(char **words, char *string)
{
	char	**join;
	int		size;
	int		i;

	if (words == NULL || string == NULL)
		return (NULL);
	size = ft_split_size(words);
	join = malloc(sizeof(char **) * (size + 2));
	if (join == NULL)
		return (NULL);
	join[size] = ft_strdup(string);
	if (join[size] != NULL)
	{
		i = 0;
		while (words[i] != NULL)
		{
			join[i] = words[i];
			i++;
		}
		join[size + 1] = NULL;
		free(words);
		return (join);
	}
	free(join);
	return (NULL);
}
