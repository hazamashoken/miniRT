/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:45:51 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/12 16:45:53 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector3.h"

int	main(int argc, char **argv)
{
	t_env	env;
	t_app	app;

	if (argc == 2)
	{
		params(argv[1], &env);
	}
	else
		return (put_err("Error\nminirt: bad arguments", NULL));
	app.data = (void *)&env;
	t_v3 v = env.shape[0]->coordinate;
	printf("shape %f, %f, %f\n", v.x, v.y, v.z);
	printf("material: %s$\n", env.shape[0]->material);
	if (env.shape[0]->type == T_SPHERE)
		printf("shape is sphere\n");
	v = env.shape[0]->rgb;
	printf("colour %f, %f, %f\n", v.x, v.y, v.z);
	v = env.cam.coordinate;
	printf("camera p %f, %f, %f\n", v.x, v.y, v.z);
	v = env.cam.orientation;
	printf("camera o %f, %f, %f\n", v.x, v.y, v.z);
	app.render = 1;
	gfx_main(&app);
	return (0);
}
