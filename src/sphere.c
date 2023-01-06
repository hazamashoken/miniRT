/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 10:53:24 by abossel           #+#    #+#             */
/*   Updated: 2023/01/06 22:12:28 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include <float.h>

/*
 * check if a ray hits a sphere
 * returns 1 if hit 0 if not
 * the intersection distance in a t_hit
 * t_hit.distance is FLT_MAX if no intersection
 */
int	sphere_hit_quick(t_ray *r, t_hit *h, t_v3 s_centre, float s_radius)
{
	t_v3	L;
	float	a;
	float	b;
	float	c;
	t_v3	sol;

	L = v3sub(r->origin, s_centre);
	a = v3dot(r->direction, r->direction);
	b = 2.0f * v3dot(r->direction, L);
	c = v3dot(L, L) - (s_radius * s_radius);
	sol = v3solve_quad(a, b, c);
	if (sol.x == 0.0f || sol.y < 0.0f || sol.z < 0.0f)
	{
		h->distance = FLT_MAX;
		return (0);
	}
	h->distance = sol.y;
	return (1);
}

/*
 * check if a ray hits a sphere
 * returns 1 if hit 0 if not
 * the intersection information in a t_hit
 * t_hit.distance is FLT_MAX if no intersection
 * also calculates intersect point, normal and reflection
 */
int	sphere_hit(t_ray *r, t_hit *h, t_v3 s_centre, float s_radius)
{
	if (!sphere_hit_quick(r, h, s_centre, s_radius))
		return (0);
	h->point = v3add(v3scale(r->direction, h->distance), r->origin);
	h->normal = v3norm(v3sub(h->point, s_centre));
	h->reflect = v3reflect(r->direction, h->normal);
	return (1);
}