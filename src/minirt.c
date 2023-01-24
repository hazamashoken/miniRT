/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:45:51 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/23 13:23:26 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector3.h"

int	main(int argc, char **argv)
{
	t_env	env;
	t_app	app;

	if (argc == 2)
		params(argv[1], &env);
	else
		return (put_err("Error\nminirt: bad arguments", NULL));
	app.data = (void *)&env;
	app.render = 1;
	gfx_main(&app);
	return (0);
}
