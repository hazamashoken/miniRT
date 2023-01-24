/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:03:02 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/23 14:45:21 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include "minirt.h"

void	rotate_camera(t_app *app, float dx, float dz)
{
	t_env	*env;

	env = (t_env *)(app->data);
	env->cur_obj->orientation = v3rotx(env->cur_obj->orientation, dx);
	env->cur_obj->orientation = v3rotz(env->cur_obj->orientation, dz);
}

void	move_camera(t_app *app, float dx, float dy, float dz)
{
	t_env	*env;

	env = (t_env *)(app->data);
	env->cur_obj->coordinate
		= v3add(env->cur_obj->coordinate, v3new(dx, dy, dz));
}

int	destroy(t_app *app)
{
	gfx_free(app, app->screen);
	printf("exiting...\n");
	exit(EXIT_SUCCESS);
	return (0);
}

void	*change_obj(void	*data, int *index)
{
	*index = 0;
	return (data);
}
