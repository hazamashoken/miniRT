/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinteger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 23:44:28 by abossel           #+#    #+#             */
/*   Updated: 2022/10/04 16:46:56 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <limits.h>

static int	ft_ismember(char c, char *set)
{
	if (set == NULL)
		return (0);
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static char	*ft_isinteger_readset(char *string, char *set)
{
	if (string == NULL || set == NULL)
		return (NULL);
	while (ft_ismember(*string, set))
		string++;
	return (string);
}

int	ft_isinteger(char *s)
{
	long long	num;
	int			neg;

	num = 0;
	neg = 1;
	if (s == NULL)
		return (0);
	s = ft_isinteger_readset(s, " \f\n\r\t\v");
	if (*s == '-')
		neg = -1;
	if (ft_ismember(*s, "+-"))
		s++;
	if (!ft_ismember(*s, "0123456789"))
		return (0);
	while (ft_ismember(*s, "0123456789"))
	{
		num = (num * 10) + (*s - '0');
		if ((num > INT_MAX && neg == 1) || (-num < INT_MIN && neg == -1))
			return (0);
		s++;
	}
	s = ft_isinteger_readset(s, " \f\n\r\t\v");
	if (*s != '\0')
		return (0);
	return (1);
}
