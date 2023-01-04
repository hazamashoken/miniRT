/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:23:10 by abossel           #+#    #+#             */
/*   Updated: 2022/08/25 16:36:31 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_add_char(char *s, char c)
{
	while (*s != '\0')
		s++;
	*s = c;
	s++;
	*s = '\0';
}

static void	ft_itoa2(int n, char *s)
{
	int		div;
	int		mod;
	char	c;

	div = n / 10;
	mod = n % 10;
	if (n < 0)
	{
		ft_add_char(s, '-');
		div = -div;
		mod = -mod;
	}
	if (div != 0)
	{
		ft_itoa2(div, s);
	}
	c = '0' + mod;
	ft_add_char(s, c);
}

char	*ft_itoa(int n)
{
	char	str[12];

	str[0] = '\0';
	ft_itoa2(n, str);
	return (ft_strdup(str));
}
