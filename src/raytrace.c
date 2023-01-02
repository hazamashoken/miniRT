/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 08:18:40 by abossel           #+#    #+#             */
/*   Updated: 2023/01/02 20:41:39 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include "mlx_render.h"
#include <math.h>

/*
 * https://www.scratchapixel.com/lessons/3d-basic-rendering/
 * minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
 */
int circle_intersect(t_v3 origin, t_v3 direction, t_v3 c_cen, float c_rad)
{
	t_v3	L;
	float	a;
	float	b;
	float	c;
	t_v3	sol;

	L = v3sub(origin, c_cen);
	a = v3dot(direction, direction);
	b = 2.0f * v3dot(direction, L);
	c = v3dot(L, L) - (c_rad * c_rad);
	sol = v3solve_quad(a, b, c);
	if (sol.x == 0.0f)
		return (0);
	if (sol.y < 0.0f && sol.z < 0.0f)
		return (0);
	return (1);
}

int	ambient_ray(t_v3 origin, t_v3 direction)
{
	if (circle_intersect(origin, direction, v3new(1.5f, 3.0f, 0.0f), 0.5f))
		return (rgb(0, 0, 255));
	if (circle_intersect(origin, direction, v3new(-1.0f, 5.0f, 1.0f), 0.5f))
		return (rgb(0, 255, 0));
	if (circle_intersect(origin, direction, v3new(0.0f, 10.0f, 0.0f), 2.0f))
		return (rgb(255, 0, 0));
	return (rgb(0, 0, 0));
}

/*
void raytrace(t_app *app, t_v3 origin, t_v3 direction, float fov_deg)
{
	float	fov;
	float	delta;
	t_v3	ray_dir;
	int		x;
	int		y;

	fov = deg2rad(fov_deg);
	delta = fov / SCR_WIDTH;
	y = 0;
	while (y < SCR_HEIGHT)
	{
		x = 0;
		while (x < SCR_WIDTH)
		{
			ray_dir = v3rotz(direction, -(fov / 2.0f) + (x * delta));
			ray_dir = v3rotx(ray_dir, -((fov * SCR_HEIGHT / SCR_WIDTH) / 2.0f) + (y * delta));
			pixel_put(app->screen, x, y, ambient_ray(origin, ray_dir));
			x++;
		}
		y++;
	}
	app->render = 1;
}
*/

void raytrace(t_app *app, t_v3 origin, t_v3 direction, float fov_deg)
{
	float	fov;
	t_v3	ray_dir;
	t_v3	axis;
	float	angle;
	int		p;

	if (fov_deg == 180.0f)
		fov_deg = 179.9f;
	axis = v3norm(v3cross(v3new(0.0f, 0.0f, -1.0f), direction));
	angle = acos(v3dot(v3new(0.0f, 0.0f, -1.0f), direction));
	fov = deg2rad(fov_deg);
	p = 0;
	while (p < SCR_WIDTH * SCR_HEIGHT)
	{
		ray_dir.x = (p % SCR_WIDTH + 0.5f) - SCR_WIDTH / 2.0f;
		ray_dir.y = -(p / SCR_WIDTH + 0.5f) + SCR_HEIGHT / 2.0f;
		ray_dir.z = -SCR_HEIGHT / (2.0f * tan(fov / 2.0f));
		ray_dir = v3rot_axis(ray_dir, axis, angle);
		ray_dir = v3norm(ray_dir);
		pixel_put(app->screen, p % SCR_WIDTH, p / SCR_WIDTH,
			ambient_ray(origin, ray_dir));
		p++;
	}
	app->render = 1;
}
