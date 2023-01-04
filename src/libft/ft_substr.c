/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:06:31 by abossel           #+#    #+#             */
/*   Updated: 2022/08/25 19:21:34 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	strlen;
	size_t	sublen;

	if (s == NULL)
		return (NULL);
	strlen = ft_strlen(s);
	if (start > strlen)
	{
		substr = malloc(1);
		if (substr != NULL)
			substr[0] = '\0';
		return (substr);
	}
	sublen = ft_strlen(&s[start]);
	if (sublen > len)
		sublen = len;
	substr = malloc(sublen + 1);
	if (substr != NULL)
	{
		ft_memcpy(substr, &s[start], sublen);
		substr[sublen] = '\0';
	}
	return (substr);
}
