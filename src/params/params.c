/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:17:13 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/11 20:44:57 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @brief set the params of minirt
/// @param file (file path)
/// @param env (main struct)
void	params(char *file, t_env *env)
{
	init_env(env);
	set_params(check_file(file), env);
	printf("%s\n", file);
}
