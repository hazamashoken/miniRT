/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:07:37 by abossel           #+#    #+#             */
/*   Updated: 2022/11/16 11:13:41 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>
#include <stdlib.h>

/*
 * join multiple strings
 * joins n strings together in a string allocated with malloc
 * example: ft_strjoinv(3, "42", " ", "school")
 * does not handle NULL strings and returns NULL on failure
 */
char	*ft_strjoinv(int n, ...)
{
	va_list	ap1;
	va_list	ap2;
	size_t	size;
	char	*join;
	int		i;

	va_start(ap1, n);
	va_copy(ap2, ap1);
	size = 1;
	i = n;
	while (i--)
		size += ft_strlen(va_arg(ap1, char *));
	va_end(ap1);
	join = malloc(size);
	if (join != NULL)
	{
		join[0] = '\0';
		i = n;
		while (i--)
			ft_strlcat(join, va_arg(ap2, char *), size);
	}
	va_end(ap2);
	return (join);
}
