/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:45:51 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/08 17:03:35 by abossel          ###   ########.fr       */
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
	t_v3 v = v4tov3(env.shape[0]->coordinate);
	printf("shape %f, %f, %f\n", v.x, v.y, v.z);
	if (env.shape[0]->type == T_SPHERE)
		printf("shape is sphere\n");
	v = v4tov3(env.cam.coordinate);
	printf("camera p %f, %f, %f\n", v.x, v.y, v.z);
	v = v4tov3(env.cam.orientation);
	printf("camera o %f, %f, %f\n", v.x, v.y, v.z);
	gfx_main(&app);
	return (0);
}
