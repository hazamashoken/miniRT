/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 21:07:28 by abossel           #+#    #+#             */
/*   Updated: 2022/08/26 16:15:42 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d == s || len == 0)
		return (dst);
	i = 0;
	while (i < len)
	{
		if (d < s)
			d[i] = s[i];
		else
			d[len - 1 - i] = s[len - 1 - i];
		i++;
	}
	return (dst);
}
