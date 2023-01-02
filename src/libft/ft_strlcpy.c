/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:03:02 by abossel           #+#    #+#             */
/*   Updated: 2022/10/27 01:00:20 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
