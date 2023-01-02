/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:24:10 by tliangso          #+#    #+#             */
/*   Updated: 2022/10/27 16:30:18 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	k;
	char	*str;

	k = 0;
	if (s1 == (void *)0 || s2 == (void *)0)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (*(s1 + i) != '\0')
		*(str + k++) = *(s1 + i++);
	i = 0;
	while (*(s2 + i) != '\0')
		*(str + k++) = *(s2 + i++);
	*(str + k) = '\0';
	return (str);
}

char	*ft_strjoin_free(char *s1, char *s2, int mode)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (mode == 0 || mode == 1)
		free(s1);
	if (mode == 0 || mode == 2)
		free(s2);
	return (str);
}
