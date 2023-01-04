/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 20:41:39 by abossel           #+#    #+#             */
/*   Updated: 2022/08/26 16:28:06 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*elem;
	t_list	*newlst;
	t_list	*newelem;

	newlst = NULL;
	newelem = NULL;
	elem = lst;
	while (elem != NULL)
	{
		newelem = ft_lstnew((*f)(elem->content));
		if (newelem == NULL)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		if (newlst == NULL)
			newlst = newelem;
		else
			ft_lstadd_back(&newlst, newelem);
		elem = elem->next;
	}
	return (newlst);
}
