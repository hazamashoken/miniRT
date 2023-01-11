/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 20:09:01 by abossel           #+#    #+#             */
/*   Updated: 2022/08/25 20:11:27 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*elem;

	elem = lst;
	while (elem != 0)
	{
		if (elem->next == 0)
			return (elem);
		elem = elem->next;
	}
	return (0);
}
