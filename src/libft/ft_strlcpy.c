/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:03:02 by abossel           #+#    #+#             */
/*   Updated: 2022/08/26 15:56:13 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstend;

	i = 0;
	dstend = 0;
	while (src[i] != '\0')
	{
		if (dstsize != 0 && i < dstsize - 1)
		{
			dst[i] = src[i];
			dstend++;
		}
		i++;
	}
	if (dstsize != 0)
		dst[dstend] = '\0';
	return (i);
}
