/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 21:27:31 by abossel           #+#    #+#             */
/*   Updated: 2022/12/30 13:14:25 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_events.h"
#include "mlx_render.h"
#include <stdlib.h>

#include "vector3.h"
void raytrace(t_app *app, t_v3 origin, t_v3 direction, float fov_deg);

int	render(t_app *app)
{
	raytrace(app, v3new(0, 0, 0), v3new(0, 1, 0), 50.0f);
	if (app->render)
	{
		mlx_put_image_to_window(app->mlx, app->win, app->screen->image, 0, 0);
		app->render = 0;
	}
	return (0);
}

int	mouse(int button, int x, int y, t_app *app)
{
	if (x >= 0 && y >= 0 && x < app->width && y < app->height)
	{
		if (button == MOUSE_SCROLL_DOWN)
			;
		else if (button == MOUSE_SCROLL_UP)
			;
	}
	app->render = 1;
	return (0);
}

int	keypress(int keycode, t_app *app)
{
	if (keycode == KEY_UP)
		;
	else if (keycode == KEY_DOWN)
		;
	else if (keycode == KEY_LEFT)
		;
	else if (keycode == KEY_RIGHT)
		;
	else if (keycode == KEY_ESCAPE)
		destroy(app);
	app->render = 1;
	return (0);
}

int	destroy(t_app *app)
{
	gfx_free(app, app->screen);
	exit(EXIT_SUCCESS);
	return (0);
}
