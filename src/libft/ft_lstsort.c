/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 07:34:43 by abossel           #+#    #+#             */
/*   Updated: 2022/12/12 12:31:44 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstsort_merge(t_list **lst, t_list **lst1, t_list **lst2,
				int (*cmp)())
{
	t_list	*head;
	t_list	*tail;

	head = 0;
	tail = 0;
	while (*lst1 != 0 && *lst2 != 0)
	{
		if (cmp((*lst1)->content, (*lst2)->content) > 0)
			ft_lstadd_back(&tail, ft_lstpop(lst2));
		else
			ft_lstadd_back(&tail, ft_lstpop(lst1));
		if (head == 0)
			head = tail;
		if (tail->next != 0)
			tail = tail->next;
	}
	if (*lst1 != 0)
		ft_lstadd_back(&tail, *lst1);
	if (*lst2 != 0)
		ft_lstadd_back(&tail, *lst2);
	ft_lstadd_back(lst, head);
}

static void	ft_lstsort_split(t_list **lst, int (*cmp)())
{
	t_list	*lst1;
	t_list	*lst2;
	t_list	*tail;
	int		split;

	split = ft_lstsize(*lst) / 2 - 1;
	tail = *lst;
	while (split > 0)
	{
		tail = tail->next;
		split--;
	}
	lst1 = *lst;
	lst2 = tail->next;
	*lst = 0;
	tail->next = 0;
	ft_lstsort(&lst1, cmp);
	ft_lstsort(&lst2, cmp);
	ft_lstsort_merge(lst, &lst1, &lst2, cmp);
}

void	ft_lstsort(t_list **lst, int (*cmp)())
{
	if (lst == 0 || *lst == 0 || (*lst)->next == 0)
		return ;
	if ((*lst)->next->next == 0)
	{
		if (cmp((*lst)->content, (*lst)->next->content) > 0)
			ft_lstadd_back(lst, ft_lstpop(lst));
		return ;
	}
	ft_lstsort_split(lst, cmp);
}
