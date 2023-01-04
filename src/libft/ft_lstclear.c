/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 20:26:21 by abossel           #+#    #+#             */
/*   Updated: 2022/08/26 16:26:11 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;
	t_list	*list;

	elem = *lst;
	while (elem != NULL)
	{
		list = elem->next;
		(*del)(elem->content);
		free(elem);
		elem = list;
	}
	*lst = NULL;
}
