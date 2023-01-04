/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 08:18:40 by abossel           #+#    #+#             */
/*   Updated: 2023/01/04 11:08:51 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "vector3.h"
#include "mlx_render.h"
#include <math.h>

int	cast_ray(t_ray r)
{
	t_hit	h;

	h = sphere_hit(r, v3new(1.5f, 3.0f, 0.0f), 0.5f);
	if (h.distance != -1.0f)
		return (rgb(0, 0, 255));
	h = sphere_hit(r, v3new(-1.0f, 5.0f, 1.0f), 0.5f);
	if (h.distance != -1.0f)
		return (rgb(0, 255, 0));
	h = sphere_hit(r, v3new(0.0f, 10.0f, 0.0f), 2.0f);
	if (h.distance != -1.0f)
		return (rgb(255, 0, 0));
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

/*
void raytrace(t_app *app, t_v3 origin, t_v3 direction, float fov_deg)
{
	float	fov;
	t_ray	r;
	t_v3	axis;
	float	angle;
	int		p;

	if (fov_deg == 180.0f)
		fov_deg = 179.9f;
	axis = v3norm(v3cross(v3new(0.0f, 0.0f, -1.0f), direction));
	angle = acos(v3dot(v3new(0.0f, 0.0f, -1.0f), direction));
	fov = deg2rad(fov_deg);
	p = 0;
	while (p < app->width * app->height)
	{
		r.origin = origin;
		r.direction.x = (p % app->width + 0.5f) - app->width / 2.0f;
		r.direction.y = -(p / app->width + 0.5f) + app->height / 2.0f;
		r.direction.z = -app->height / (2.0f * tan(fov / 2.0f));
		r.direction = v3rot_axis(r.direction, axis, angle);
		r.direction = v3norm(r.direction);
		pixel_put(app->screen, p % app->width, p / app->width,
			ambient_ray(r.origin, r.direction));
		p++;
	}
	app->render = 1;
}
*/
