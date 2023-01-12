/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:36:58 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/12 12:13:48 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @brief init env with 0 or NULL as default
/// @param env (main struct)
void	init_env(t_env *env)
{
	env->cam.coordinate.x = 0;
	env->cam.coordinate.y = 0;
	env->cam.coordinate.z = 0;
	env->cam.fov = 0;
	env->cam.orientation.x = 0;
	env->cam.orientation.y = 0;
	env->cam.orientation.z = 0;
	env->amb.brightness = 0;
	env->amb.rgb.r = 0;
	env->amb.rgb.g = 0;
	env->amb.rgb.b = 0;
	env->light = NULL;
	env->shape = NULL;
}

void	free_env(t_env *env)
{
	if (env->light)
	{
		nta_free((void **)env->light);
		env->light = NULL;
	}
	if (env->shape)
	{
		nta_free((void **)env->shape);
		env->shape = NULL;
	}
}

/// @brief set char **rgb values then nta_free the values
/// @param values (string of rgb)
/// @return t_rgb type vector
void	set_rgb(char **values, t_v3 *rgb)
{
	rgb->r = ft_atoi(values[0]);
	rgb->g = ft_atoi(values[1]);
	rgb->b = ft_atoi(values[2]);
	nta_free((void **)values);
}

/// @brief set t_v4sd then free nta_free the values
/// @param values
/// @return t_v4sd vector with magnitute
void	set_vector(char **values, t_v3 *vector)
{
	vector->x = ft_atod(values[0]);
	vector->y = ft_atod(values[1]);
	vector->z = ft_atod(values[2]);
	nta_free((void **)values);
}
