/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 21:02:27 by abossel           #+#    #+#             */
/*   Updated: 2023/01/04 11:36:52 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

static double	ft_atof_fractional(const char *frac)
{
	double	number;
	int		i;

	number = ft_atoi(frac);
	i = ft_strlen(frac);
	while (i > 0)
	{
		number /= 10.0;
		i--;
	}
	return (number);
}

double	ft_atof(const char *str)
{
	double	number;
	char	integral[256];
	char	*frac;

	number = 0.0;
	ft_strlcpy(integral, str, 256);
	frac = ft_strchr(integral, '.');
	if (frac != NULL)
	{
		*frac = '\0';
		frac++;
		if (!ft_isinteger(frac) || frac[0] == '-' || frac[0] == '+')
			return (0.0);
		number = ft_atof_fractional(frac);
	}
	if (!ft_isinteger(integral))
		return (0.0);
	if (integral[0] == '-')
		return (ft_atoi(integral) - number);
	return (ft_atoi(integral) + number);
}

double	ft_atod(const char *str)
{
	return (ft_atof(str));
}
