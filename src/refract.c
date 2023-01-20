/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:02:48 by abossel           #+#    #+#             */
/*   Updated: 2023/01/20 20:57:58 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "raytrace.h"
#include "vector3.h"
#include <math.h>

/*
 * return the intersection point from inside the sphere
 */
float	sphere_hit_refract(t_ray *r, t_hit *h, t_obj *shape)
{
	t_v3	l;
	t_v3	q;
	t_v3	s;
	float	d2;

	l = v3sub(r->origin, shape->coordinate);
	q.v[0] = v3dot(r->direction, r->direction);
	q.v[1] = 2.0f * v3dot(r->direction, l);
	q.v[2] = v3dot(l, l) - ((shape->diameter / 2.0f) * (shape->diameter / 2.0f));
	s = v3solve_quad(q.v[0], q.v[1], q.v[2]);
	if (s.v[0] == 0.0f)
		return (0.0f);
	h->distance = s.v[2];
	h->point = v3add(v3scale(r->direction, h->distance), r->origin);
	h->normal = v3norm(v3sub(h->point, shape->coordinate));
	return (1);
}

/*
 * returns 1 if the ray is refracted or 0 if reflected
 * refract_i is incoming refractive index
 * refract_o is outgoing refractive index
 */
int	is_refract(t_v3 direction, t_v3 normal, float refract_i, float refract_o)
{
	float	n;
	float	cos_i;
	float	sin_t2;

	n = refract_i / refract_o;
	cos_i = -v3dot(normal, direction);
	sin_t2 = n * n * (1.0f - cos_i * cos_i);
	if (sin_t2 > 1.0f)
		return (0);
	return (1);
}

/*
 * returns the refracted ray
 * refract_i is incoming refractive index
 * refract_o is outgoing refractive index
 */
t_v3	refract(t_v3 direction, t_v3 normal, float refract_i, float refract_o)
{
	float	n;
	float	cos_i;
	float	cos_t;
	float	sin_t2;
	t_v3	refract;

	n = refract_i / refract_o;
	cos_i = -v3dot(normal, direction);
	sin_t2 = n * n * (1.0f - cos_i * cos_i);
	if (sin_t2 > 1.0f)
		return (v3reflect(direction, normal));
	cos_t = sqrt(1.0f - sin_t2);
	refract = v3scale(direction, n);
	refract = v3add(refract, v3scale(normal, n * cos_i - cos_t));
	return (v3norm(refract));
}

/*
int	ref_phong_lighting(t_env *env, t_ray *r, t_hit *h, int ref_colour)
{
	t_v3	light_dir;
	t_v3	colour;
	t_mat	m;
	float	intensity;
	int		i;

	m = get_material("glass");
	colour = irgbtov3(ref_colour);
	i = nta_size((void **)(env->light));
	while (i--)
	{
		if (light_hit(env, h->point, env->light[i]))
		{
			light_dir = v3norm(v3sub(h->point, env->light[i]->coordinate));
			intensity = phong_lighting(r, h, &m, light_dir);
			colour = v3add(colour, v3scale(env->light[i]->rgb, intensity));
		}
	}
	return (v3toirgb(v3clamp(colour, 0.0f, 255.0f)));
}
*/

/*
 * refractive index of air is 1.0, glass is 1.5
 */
int refract_ray(t_env *env, t_ray *r, t_hit *h, t_obj *shape)
{
	t_ray	r_ray;
	t_hit	r_hit;
	int		r_col;

	if (!is_refract(r->direction, h->normal, 1.0f, 1.5f))
		return (mirror_ray(env, h));
	r_ray.direction = refract(r->direction, h->normal, 1.0f, 1.5f);
	r_ray.origin = h->point;
	sphere_hit_refract(&r_ray, &r_hit, shape);
	r_ray.direction = refract(r_ray.direction, r_hit.normal, 1.5f, 1.0f);
	r_ray.origin = r_hit.point;
	r_col = cast_ray(env, &r_ray);
	return (r_col);
}
