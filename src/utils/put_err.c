/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_err.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:54:19 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/30 11:44:20 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @brief write str and arg to STDERR_FILENO
/// @param str (error message)
/// @param arg (NULLABLE if N.A)
/// @return error signal of 1
int	put_err(char *str, char *arg)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	if (arg)
		write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "\n", 1);
	return (1);
}

/// @brief write str and arg to STDERR_FILENO then exit
/// @param str (error message)
/// @param arg (NULLABLE if N.A)
void	exit_err(char *str, char *arg)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	if (arg)
		write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

/// @brief perror str then exit
/// @param str (error message)
void	exit_perr(char *str)
{
	perror(str);
	exit(1);
}
