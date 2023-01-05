/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:45:51 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/05 10:46:05 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_env	env;
	t_app	app;

	/*
	if (argc == 2)
	{
		params(argv[1], &env);
	}
	else
		return (put_err("Error\nminirt: bad arguments", NULL));
	*/
	gfx_main(&app);
	return (0);
}
