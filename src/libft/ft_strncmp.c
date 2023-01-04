/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 09:13:54 by abossel           #+#    #+#             */
/*   Updated: 2022/08/26 15:59:33 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_to_byte(char c)
{
	int	b;

	b = c;
	if (b < 0)
		b += 256;
	return (b);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		result;
	size_t	i;

	result = 0;
	i = 0;
	while ((*s1 != '\0' || *s2 != '\0') && i < n)
	{
		if (*s1 != *s2)
		{
			result = char_to_byte(*s1) - char_to_byte(*s2);
			break ;
		}
		s1++;
		s2++;
		i++;
	}
	return (result);
}
