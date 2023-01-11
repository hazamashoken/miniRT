/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 08:41:20 by abossel           #+#    #+#             */
/*   Updated: 2022/08/31 20:53:06 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last;
	char	ch;

	ch = c;
	last = NULL;
	while (*s != '\0')
	{
		if (*s == ch)
			last = (char *)s;
		s++;
	}
	if (ch == 0)
		return ((char *)s);
	return (last);
}
