/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 19:03:42 by abossel           #+#    #+#             */
/*   Updated: 2022/08/26 15:39:38 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		div;
	int		mod;
	char	c;

	div = n / 10;
	mod = n % 10;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		div = -div;
		mod = -mod;
	}
	if (div != 0)
	{
		ft_putnbr_fd(div, fd);
	}
	c = '0' + mod;
	ft_putchar_fd(c, fd);
}
