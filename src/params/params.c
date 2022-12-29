/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:17:13 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/29 17:41:02 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	check_extension(char *file)
{
	if (ft_strrchr(file, '.') == NULL)
		exit_err("Error\nminirt: wrong file extension: ", file);
	if (ft_strncmp(ft_strrchr(file, '.'), ".rt", 4) != 0)
		exit_err("Error\nminirt: wrong file extension: ", file);
}

void	params(char *file, t_env *env)
{
	check_extension(file);
	printf("%s\n", file);
}
