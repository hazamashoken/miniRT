/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:12:51 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/12 17:13:17 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	in_charset(char c, char *charset)
{
	while (*charset != '\0')
	{
		if (c == *charset)
			return (1);
		charset++;
	}
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	in_word;
	int	word_count;

	in_word = 0;
	word_count = 0;
	while (*str != '\0')
	{
		if (!in_word && !in_charset(*str, charset))
		{
			in_word = 1;
			word_count++;
		}
		else if (in_word && in_charset(*str, charset))
		{
			in_word = 0;
		}
		str++;
	}
	return (word_count);
}

int	word_length(char *str, char *charset)
{
	int	count;

	count = 0;
	while (*str != '\0' && !in_charset(*str, charset))
	{
		count++;
		str++;
	}
	return (count);
}

void	split_words(char **words, char *str, char *charset)
{
	int		in_word;
	int		word_count;
	char	*word_iter;

	in_word = 0;
	word_count = 0;
	while (*str != '\0')
	{
		if (!in_charset(*str, charset))
		{
			if (!in_word)
			{
				words[word_count] = malloc(word_length(str, charset) + 1);
				word_iter = words[word_count];
				word_count++;
			}
			in_word = 1;
			*word_iter = *str;
			word_iter++;
			*word_iter = '\0';
		}
		else if (in_charset(*str, charset))
			in_word = 0;
		str++;
	}
}

char	**ft_split_str(char *str, char *charset)
{
	char	**words;
	int		word_count;

	if (str == NULL || charset == NULL)
		return (NULL);
	word_count = count_words(str, charset);
	words = malloc(sizeof(char *) * (word_count + 1));
	if (words != NULL)
	{
		split_words(words, str, charset);
		words[word_count] = NULL;
	}
	return (words);
}
