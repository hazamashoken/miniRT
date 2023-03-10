/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:03:02 by abossel           #+#    #+#             */
/*   Updated: 2022/08/26 15:56:35 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	rem_size;
	size_t	dest_len;
	size_t	copy_len;

	rem_size = dstsize;
	dest_len = 0;
	while (dst[dest_len] != '\0' && rem_size > 0)
	{
		dest_len++;
		rem_size--;
	}
	if (dst[dest_len] == '\0' || rem_size != 0)
	{
		copy_len = 0;
		while (src[copy_len] != '\0' && rem_size > 1)
		{
			dst[dest_len + copy_len] = src[copy_len];
			copy_len++;
			rem_size--;
		}
		dst[dest_len + copy_len] = '\0';
	}
	return (dest_len + ft_strlen(src));
}
