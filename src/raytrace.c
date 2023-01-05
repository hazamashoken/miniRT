/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 08:18:40 by abossel           #+#    #+#             */
/*   Updated: 2023/01/06 00:00:44 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "vector3.h"
#include "mlx_render.h"
#include <math.h>

/*
 * calculate phong lighting for a single light source
 * I = Kd * (N dot L) + Ks * (R dot V) ^ Ka
 * N = surface normal
 * L = unit vector from intersection point and light
 * V = unit vector from intersection point and camera
 * R = light reflection unit vector
 * Kd = diffuse reflectivity
 * Ks = specular reflectivity
 * Ka = shinyness
 */
float	phong_lighting(t_ray *r, t_hit *h, t_mat *m, t_v3 light_dir)
{
	t_v3	camera_dir;
	t_v3	reflect_dir;
	float	intensity;

	camera_dir = v3norm(v3sub(r->origin, h->point));
	reflect_dir = v3norm(v3reflect(light_dir, h->normal));
	intensity = m->diffuse * v3dot(v3neg(light_dir), h->normal)
		+ m->specular * pow(v3dot(reflect_dir, camera_dir), m->shine);
	intensity = clamp(intensity, 0.0f, 1.0f);
	return (intensity);
}

/*
 * calculate diffuse lighting for a single light source
 * I = Kd * (N dot L)
 * N = surface normal
 * L = unit vector from intersection point and light
 * Kd = diffuse reflectivity
 */
float	diffuse_lighting(t_ray *r, t_hit *h, t_mat *m, t_v3 light_dir)
{
	float	intensity;

	intensity = m->diffuse * v3dot(v3neg(light_dir), h->normal);
	intensity = clamp(intensity, 0.0f, 1.0f);
	return (intensity);
}

int	cast_ray(t_ray r);

int	cast_mirror_ray(t_ray *r, t_hit *h)
{
	t_ray	reflect_ray;

	reflect_ray.direction = v3norm(v3reflect(r->direction, h->normal));
	reflect_ray.origin = h->point;
	return (cast_ray(reflect_ray));
}

int	cast_shadow_ray(t_ray r)
{
	t_hit	h;

	h = sphere_hit(r, v3new(0.0f, 3.5f, 1.0f), 0.5f);
	if (h.distance >= 0.0f)
		return (1);
	h = sphere_hit(r, v3new(0.0f, 3.25f, -0.5f), 0.5f);
	if (h.distance >= 0.0f)
		return (1);
	h = sphere_hit(r, v3new(0.0f, 10.0f, 0.0f), 2.0f);
	if (h.distance >= 0.0f)
		return (1);
	return (0);
}

int	cast_ray(t_ray r)
{
	t_hit	h;
	float	ratio;
	t_v3	light;
	t_v3	light_dir;
	t_mat	m;
	t_ray	sr;

	m.specular = 1.5f;
	m.diffuse = 0.8f;
	m.ambient = 0.6f;
	m.shine = 125.0f;
	light = v3new(0.0f, 0.0f, 20.0f);
	light_dir = v3norm(v3sub(h.point, light));

	h = sphere_hit(r, v3new(0.0f, 3.5f, 1.0f), 0.5f);
	if (h.distance != -1.0f)
	{
		sr.origin = h.point;
		sr.direction = v3neg(light_dir);
		if (cast_shadow_ray(sr))
			return (rgb(0, 0, 0));
		return (rgb(0, 0, 255.0f * phong_lighting(&r, &h, &m, light_dir)));
	}
	h = sphere_hit(r, v3new(0.0f, 3.25f, -0.5f), 0.5f);
	if (h.distance != -1.0f)
	{
		sr.origin = h.point;
		sr.direction = v3neg(light_dir);
		if (cast_shadow_ray(sr))
			return (rgb(0, 0, 0));
		return (rgb(0, 255.0f * phong_lighting(&r, &h, &m, light_dir), 0));
	}
	h = sphere_hit(r, v3new(0.0f, 10.0f, 0.0f), 2.0f);
	if (h.distance != -1.0f)
	{
		sr.origin = h.point;
		sr.direction = v3neg(light_dir);
		if (cast_shadow_ray(sr))
			return (rgb(0, 0, 0));
		//return (rgb(255.0f * diffuse_lighting(&r, &h, &m, light_dir), 0, 0));
		return (cast_mirror_ray(&r, &h));
	}
	return (rgb(0, 0, 0));
}

/*
 * raytrace a scene
 * default camera orientation (0, 0, 0)
 * +y axis is forward
 * +x axis is right
 * +z axis is up
 * values go from -1 to 1 (-180 to 180 deg) or (-pi to pi rad)
 * direction.z is inverted because in screen y coordinates are inverted
 */
/*
void raytrace(t_app *app, t_v3 origin, t_v3 orient, float fov_degrees)
{
	float	fov;
	t_ray	r;
	int		p;

	if (fov_degrees == 180.0f)
		fov_degrees = 179.9f;
	fov = deg2rad(fov_degrees);
	p = 0;
	while (p < app->width * app->height)
	{
		r.origin = origin;
		r.direction.x = (p % app->width + 0.5f) - app->width / 2.0f;
		r.direction.y = app->height / (2.0f * tan(fov / 2.0f));
		r.direction.z = -(p / app->width + 0.5f) + app->height / 2.0f;
		r.direction = v3rotx(r.direction, orient.x * M_PI);
		r.direction = v3roty(r.direction, orient.y * M_PI);
		r.direction = v3rotz(r.direction, orient.z * M_PI);
		r.direction = v3norm(r.direction);
		pixel_put(app->screen, p % app->width, p / app->width, cast_ray(r));
		p++;
	}
	app->render = 1;
}
*/

/*
 * raytrace a scene
 * default camera orientation
 * +y axis is forward
 * +x axis is right
 * +z axis is up
 * direction is the normalized direction of the camera
 * direction.z is inverted because in screen y coordinates are inverted
 */
void raytrace(t_app *app, t_v3 origin, t_v3 direction, float fov_degrees)
{
	float	fov;
	t_ray	r;
	t_v3	axis;
	float	angle;
	int		p;

	if (fov_degrees == 180.0f)
		fov_degrees = 179.9f;
	axis = v3norm(v3cross(v3new(0.0f, 1.0f, 0.0f), direction));
	angle = acos(v3dot(v3new(0.0f, 1.0f, 0.0f), direction));
	fov = deg2rad(fov_degrees);
	p = 0;
	while (p < app->width * app->height)
	{
		r.origin = origin;
		r.direction.x = (p % app->width + 0.5f) - app->width / 2.0f;
		r.direction.y = app->height / (2.0f * tan(fov / 2.0f));
		r.direction.z = -(p / app->width + 0.5f) + app->height / 2.0f;
		r.direction = v3norm(v3rot_axis(r.direction, axis, angle));
		pixel_put(app->screen, p % app->width, p / app->width,
			cast_ray(r));
		p++;
	}
	app->render = 1;
}
