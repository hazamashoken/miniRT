/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 08:18:40 by abossel           #+#    #+#             */
/*   Updated: 2023/01/08 20:15:47 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "vector3.h"
#include "mlx_render.h"
#include <float.h>
#include <math.h>

/*
int	cast_mirror_ray(t_ray *r, t_hit *h)
{
	t_ray	reflect_ray;

	reflect_ray.direction = v3norm(v3reflect(r->direction, h->normal));
	reflect_ray.origin = h->point;
	return (cast_ray(reflect_ray));
}
*/

int	cast_ray2(t_env *env, t_ray *r, t_shape *s)
{
	t_mat	m;
	t_hit	h;
	t_v3	light_dir;
	t_v3	colour;
	float	intensity;
	int		i;

	m.specular = 1.5f;
	m.diffuse = 0.8f;
	m.ambient = 0.6f;
	m.shine = 125.0f;
	// set ambient here
	colour = v3scale(v3new(1.0f, 50.0f, 1.0f), 1.0f);
	h = shape_hit(r, s);
	i = 0;
	while (env->light[i] != NULL && light_hit(env, h.point, env->light[i]))
	{
		light_dir = v3norm(v3sub(h.point, v4tov3(env->light[i]->coordinate)));
		intensity = phong_lighting(r, &h, &m, light_dir);
		// get shape rgb
		colour = v3add(colour, v3scale(v3new(0.0f, 128.0f, 0.0f), intensity));
		i++;
	}
	return (v3toirgb(v3clamp(colour, 0.0f, 255.0f)));
}

int	cast_ray(t_env *env, t_ray *r)
{
	t_shape	*shape;

	shape = find_shape(env, r);
	if (shape == NULL)
		return (rgb(0, 0, 0));
	return (cast_ray2(env, r, shape));
}

/*
 * raytrace a scene
 * default camera orientation
 * +y axis is forward
 * +x axis is right
 * +z axis is up
 * direction is the normalized direction of the camera
 * direction.z is inverted because in screen y coordinates are inverted
 */
void raytrace(t_app *app, t_env *env)
{
	float	fov;
	t_ray	r;
	t_v3	axis;
	float	angle;
	int		p;

	if (env->cam.fov == 180.0)
		fov = deg2rad(179.9f);
	else
		fov = deg2rad(env->cam.fov);
	axis = v3norm(v3cross(v3new(0.0f, 1.0f, 0.0f), v4tov3(env->cam.orientation)));
	angle = acos(v3dot(v3new(0.0f, 1.0f, 0.0f), v4tov3(env->cam.orientation)));
	p = 0;
	while (p < app->width * app->height)
	{
		r.origin = v4tov3(env->cam.coordinate);
		r.direction.x = (p % app->width + 0.5f) - app->width / 2.0f;
		r.direction.y = app->height / (2.0f * tan(fov / 2.0f));
		r.direction.z = -(p / app->width + 0.5f) + app->height / 2.0f;
		r.direction = v3norm(v3rot_axis(r.direction, axis, angle));
		pixel_put(app->screen, p % app->width, p / app->width, cast_ray(env, &r));
		p++;
	}
	app->render = 1;
}