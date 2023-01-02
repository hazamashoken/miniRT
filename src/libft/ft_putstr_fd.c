/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 21:25:37 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/06 10:55:31 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_putstr_fd(char *str, int fd)
{
	int	len;

	if (fd < 0)
		return (-1);
	len = 0;
	while (str[len])
		len++;
	return (write(fd, str, len));
}
