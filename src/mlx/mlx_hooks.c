/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 21:27:31 by abossel           #+#    #+#             */
/*   Updated: 2023/01/23 13:48:30 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt_mlx.h"
#include "mlx_render.h"
#include "minirt.h"
#include <stdlib.h>

#include "vector3.h"
#include "raytrace.h"

int	render(t_app *app)
{
	if (app->render)
	{
		raytrace(app, (t_env *)(app->data));
		mlx_put_image_to_window(app->mlx, app->win, app->screen->image, 0, 0);
		app->render = 0;
	}
	return (0);
}

// int	mouse(int button, int x, int y, t_app *app)
// {
// 	if (x >= 0 && y >= 0 && x < app->width && y < app->height)
// 	{
// 		if (button == MOUSE_SCROLL_DOWN)
// 		{
// 		}
// 		else if (button == MOUSE_SCROLL_UP)
// 		{
// 		}
// 	}
// 	app->render = 1;
// 	return (0);
// }
static void	print_cur_obj(int type, int index, t_env *env)
{
	if (type == 0)
		printf("light[%d] selected\n", index);
	else if (type == 1)
		printf("shape[%d]: %d selected\n", index, env->cur_obj->type);
	else
		printf("camera selected\n");
}

static void	change_object(t_app *app)
{
	t_env		*env;
	static int	type;
	static int	index;

	env = (t_env *)(app->data);
	if (env->cur_obj == &(env->cam))
	{
		env->cur_obj = change_obj(env->light[0], &index);
		type = 0;
	}
	else if (type == 0 && index < env->light_count - 1)
		env->cur_obj = env->light[++index];
	else if (type == 0 && type++)
		env->cur_obj = change_obj(env->shape[0], &index);
	else if (type == 1 && index < env->shape_count - 1)
		env->cur_obj = env->shape[++index];
	else if (type == 1 && type++)
		env->cur_obj = change_obj(&(env->cam), &index);
	print_cur_obj(type, index, env);
}

static inline int	keypress2(int keycode, t_app *app)
{
	if (keycode == KEY_W)
		move_camera(app, 0, 1, 0);
	else if (keycode == KEY_A)
		move_camera(app, -1, 0, 0);
	else if (keycode == KEY_S)
		move_camera(app, 0, -1, 0);
	else if (keycode == KEY_D)
		move_camera(app, 1, 0, 0);
	else if (keycode == KEY_R)
		move_camera(app, 0, 0, 1);
	else if (keycode == KEY_F)
		move_camera(app, 0, 0, -1);
	else
		return (1);
	return (0);
}

int	keypress(int keycode, t_app *app)
{
	if (keycode == KEY_UP)
		rotate_camera(app, 0.2, 0);
	else if (keycode == KEY_DOWN)
		rotate_camera(app, -0.2, 0);
	else if (keycode == KEY_LEFT)
		rotate_camera(app, 0, 0.2);
	else if (keycode == KEY_RIGHT)
		rotate_camera(app, 0, -0.2);
	else if (keycode == KEY_ESCAPE)
		destroy(app);
	else if (keycode == KEY_TAB)
		return (change_object(app), 0);
	else if (keypress2(keycode, app))
		return (0);
	raytrace(app, (t_env *)(app->data));
	return (0);
}
