/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 20:15:14 by abossel           #+#    #+#             */
/*   Updated: 2022/08/25 20:22:53 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*back;

	back = *lst;
	if (back == 0)
	{
		*lst = new;
	}
	while (back != 0)
	{
		if (back->next == 0)
		{
			back->next = new;
			return ;
		}
		back = back->next;
	}
}
