/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:43:42 by abossel           #+#    #+#             */
/*   Updated: 2022/09/28 17:25:28 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	count_words(char *str, char c)
{
	int	in_word;
	int	word_count;

	in_word = 0;
	word_count = 0;
	while (*str != '\0')
	{
		if (!in_word && *str != c)
		{
			in_word = 1;
			word_count++;
		}
		else if (in_word && *str == c)
		{
			in_word = 0;
		}
		str++;
	}
	return (word_count);
}

static int	word_length(char *str, char c)
{
	int	length;

	length = 0;
	while (*str != '\0' && *str != c)
	{
		length++;
		str++;
	}
	return (length);
}

static int	split_words(char **words, char *str, char c)
{
	int		word_count;
	int		word_len;

	word_count = 0;
	while (*str != '\0')
	{
		if (*str != c)
		{
			word_len = word_length(str, c);
			words[word_count] = ft_substr(str, 0, word_len);
			if (words[word_count] == NULL)
				return (0);
			word_count++;
			str += word_len;
		}
		else
			str++;
	}
	words[word_count] = NULL;
	return (1);
}

static void	free_words(char **words)
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

char	**ft_split(char const *s, char c)
{
	char	**words;
	char	*str;
	char	zero;
	int		word_count;

	zero = '\0';
	str = (char *)s;
	if (str == NULL)
		str = &zero;
	word_count = count_words(str, c);
	words = malloc(sizeof(char *) * (word_count + 1));
	if (words != NULL)
	{
		if (!split_words(words, str, c))
		{
			free_words(words);
			return (NULL);
		}
		words[word_count] = NULL;
	}
	return (words);
}
