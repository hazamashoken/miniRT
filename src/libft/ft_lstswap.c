/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:16:08 by abossel           #+#    #+#             */
/*   Updated: 2022/11/17 09:38:00 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * swap 2 nodes in a linked list via memcpy
 * useful for adding a node to the front of a list without t_list**
 * add the node to 2nd position then swap 1st and 2nd
 */
void	ft_lstswap(t_list *node1, t_list *node2)
{
	t_list	temp;

	if (node1 == node2)
		return ;
	temp.next = node1->next;
	node1->next = node2->next;
	node2->next = temp.next;
	ft_memcpy(&temp, node1, sizeof(t_list));
	ft_memcpy(node1, node2, sizeof(t_list));
	ft_memcpy(node2, &temp, sizeof(t_list));
}
