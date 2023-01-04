/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:37:58 by abossel           #+#    #+#             */
/*   Updated: 2022/09/21 16:03:17 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*m;
	size_t	bytes;

	if (count == 0 || size == 0)
		return (NULL);
	bytes = count * size;
	if (bytes / size != count)
		return (NULL);
	m = malloc(bytes);
	if (m != NULL)
		ft_memset(m, 0, bytes);
	return (m);
}
