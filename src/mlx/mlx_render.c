/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 21:17:06 by abossel           #+#    #+#             */
/*   Updated: 2022/12/30 09:47:07 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mlx.h"
#include "mlx_events.h"
#include "mlx_render.h"

int	gfx_init(t_app *app, t_image *screen)
{
	app->mlx = NULL;
	app->win = NULL;
	app->screen = NULL;
	screen->image = NULL;
	app->mlx = mlx_init();
	if (app->mlx != NULL)
	{
		app->win = mlx_new_window(app->mlx, SCR_WIDTH, SCR_HEIGHT, "raytracer");
		if (app->win != NULL)
		{
			app->width = SCR_WIDTH;
			app->height = SCR_HEIGHT;
			app->render = 1;
			screen->image = mlx_new_image(app->mlx, SCR_WIDTH, SCR_HEIGHT);
			if (screen->image != NULL)
			{
				screen->addr = mlx_get_data_addr(screen->image, &(screen->bpp),
						&(screen->width), &(screen->endian));
				return (1);
			}
		}
	}
	gfx_free(app, screen);
	return (0);
}

void	gfx_free(t_app *app, t_image *screen)
{
	if (screen->image != NULL)
		mlx_destroy_image(app->mlx, screen->image);
	if (app->win != NULL)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx != NULL)
		free(app->mlx);
	screen->image = NULL;
	app->win = NULL;
	app->mlx = NULL;
}

void	pixel_put(t_image *img, int x, int y, int colour)
{
	char	*dst;

	dst = img->addr + (y * img->width + x * (img->bpp / 8));
	*(unsigned int *)dst = colour;
}

int	gfx_main(t_app *app)
{
	t_image		screen;

	if (!gfx_init(app, &screen))
		return (0);
	app->screen = &screen;
	mlx_hook(app->win, ON_DESTROY, 0, destroy, app);
	mlx_mouse_hook(app->win, mouse, app);
	mlx_key_hook(app->win, keypress, app);
	mlx_loop_hook(app->mlx, render, app);
	mlx_loop(app->mlx);
	gfx_free(app, &screen);
	return (1);
}
