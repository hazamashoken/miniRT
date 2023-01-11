/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_check_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:43:17 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/11 20:43:43 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @brief check file extension and return the fd if file path can be open()
/// @param file (file path)
/// @return fd of the opened file
int	check_file(char *file)
{
	int	fd;

	if (ft_strrchr(file, '.') == NULL)
		exit_err("Error\nminirt: wrong file extension: ", file);
	if (ft_strncmp(ft_strrchr(file, '.'), ".rt", 4) != 0)
		exit_err("Error\nminirt: wrong file extension: ", file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_perr("Error\nminirt");
	return (fd);
}
