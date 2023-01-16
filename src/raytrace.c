/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 08:18:40 by abossel           #+#    #+#             */
/*   Updated: 2023/01/16 13:00:06 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "vector3.h"
#include "mlx_render.h"
#include <float.h>
#include <math.h>

int	cast_ray(t_env *env, t_ray *r);

int	mirror_ray(t_env *env, t_hit *h)
{
	t_ray	reflect_ray;

	reflect_ray.direction = h->reflect;
	reflect_ray.origin = h->point;
	return (cast_ray(env, &reflect_ray));
}

/*
t_v3	colour_transfer_ray(t_env *env, t_ray *r, t_hit *h, t_shape *s,
	t_mat *m)
{
	float	intensity;
	t_v3	colour;

	intensity = diffuse_lighting(r, h, m, v3neg(h->reflect));
	colour = v3scale(reflect_colour(rgbtov3(s->rgb),
		v3scale(irgbtov3(mirror_ray(env, r, h)), intensity)), m->ambient);
	return (colour);
}
*/

int	cast_ray3(t_env *env, t_ray *r, t_hit *h, t_shape *s)
{
	t_v3	light_dir;
	t_v3	colour;
	t_mat	m;
	float	intensity;
	int		i;

	m = get_material(s->material);
	colour = v3scale(env->amb.rgb, env->amb.brightness * m.ambient);
	colour = reflect_colour(s->rgb, colour);
	if (ft_strncmp(s->material, "checkerboard", 13) == 0
		&& checkerboard_black(h, 10.0f))
	{
		colour = v3scale(env->amb.rgb, env->amb.brightness * m.ambient);
		colour = reflect_colour(v3zero(), colour);
	}
	i = nta_size((void **)(env->light));
	while (i--)
		if (light_hit(env, h->point, env->light[i]))
		{
			light_dir = v3norm(v3sub(h->point, env->light[i]->coordinate));
			intensity = phong_lighting(r, h, &m, light_dir);
			colour = v3add(colour, reflect_colour(s->rgb,
				v3scale(env->light[i]->rgb, intensity)));
		}
	return (v3toirgb(v3clamp(colour, 0.0f, 255.0f)));
}

int	cast_ray2(t_env *env, t_ray *r, t_shape *s)
{
	t_hit	h;

	h = shape_hit(r, s);
	if (ft_strncmp(s->material, "metal", 6) == 0)
		return (mirror_ray(env, &h));
	if (ft_strncmp(s->material, "bumpymetal", 11) == 0)
	{
		h.normal = v3norm(v3add(h.normal,
			v3rot_rel(bumpmap_normal(&h), v3unitz(), h.normal)));
		h.reflect = v3reflect(r->direction, h.normal);
		return (mirror_ray(env, &h));
	}
	if (ft_strncmp(s->material, "bumpy", 6) == 0)
		h.normal = v3norm(v3add(h.normal,
			v3rot_rel(bumpmap_normal(&h), v3unitz(), h.normal)));
	return (cast_ray3(env, r, &h, s));
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
	axis = v3norm(v3cross(v3new(0.0f, 1.0f, 0.0f), env->cam.orientation));
	angle = acos(v3dot(v3new(0.0f, 1.0f, 0.0f), env->cam.orientation));
	p = 0;
	while (p < app->width * app->height)
	{
		r.origin = env->cam.coordinate;
		r.direction.x = (p % app->width + 0.5f) - app->width / 2.0f;
		r.direction.y = app->height / (2.0f * tan(fov / 2.0f));
		r.direction.z = -(p / app->width + 0.5f) + app->height / 2.0f;
		r.direction = v3norm(v3rot_axis(r.direction, axis, angle));
		pixel_put(app->screen, p % app->width, p / app->width, cast_ray(env, &r));
		p++;
	}
}
