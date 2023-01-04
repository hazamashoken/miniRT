/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 14:53:19 by abossel           #+#    #+#             */
/*   Updated: 2022/08/26 16:11:53 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		leftdone;
	size_t	left;
	size_t	right;
	size_t	i;

	i = 0;
	left = 0;
	leftdone = 0;
	right = 0;
	while (s1 != NULL && set != NULL && s1[i] != '\0')
	{
		if (ft_strchr((char *)set, s1[i]))
		{
			if (!leftdone)
				left++;
			right++;
		}
		else
		{
			leftdone = 1;
			right = 0;
		}
		i++;
	}
	return (ft_substr(s1, left, i - right - left));
}
