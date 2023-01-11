/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 20:04:12 by abossel           #+#    #+#             */
/*   Updated: 2022/08/25 20:58:19 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*elem;
	int		size;

	size = 0;
	elem = lst;
	while (elem != 0)
	{
		elem = elem->next;
		size++;
	}
	return (size);
}
