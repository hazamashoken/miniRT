/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 21:07:28 by abossel           #+#    #+#             */
/*   Updated: 2022/08/26 16:14:00 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*mem;
	size_t			i;

	mem = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		mem[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
