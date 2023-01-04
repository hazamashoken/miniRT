/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 09:13:54 by abossel           #+#    #+#             */
/*   Updated: 2022/08/26 16:00:07 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	hlen;
	size_t	nlen;
	size_t	i;

	hlen = ft_strlen(haystack);
	nlen = ft_strlen(needle);
	if (nlen == 0)
		return ((char *)haystack);
	if (nlen > hlen || nlen > len)
		return (NULL);
	i = 0;
	while (i < hlen - nlen + 1 && i < len - nlen + 1)
	{
		if (ft_strncmp(haystack, needle, nlen) == 0)
			return ((char *)haystack);
		haystack++;
		i++;
	}
	return (NULL);
}
