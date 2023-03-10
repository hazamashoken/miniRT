/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 10:53:24 by abossel           #+#    #+#             */
/*   Updated: 2023/01/19 11:26:27 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

/*
 * check if a ray hits a sphere
 * returns 1 if hit 0 if not
 * the intersection distance is in a t_hit
 */
int	sphere_hit_quick(t_ray *r, t_hit *h, t_obj *s)
{
	t_v3	l;
	float	a;
	float	b;
	float	c;
	t_v3	sol;

	l = v3sub(r->origin, s->coordinate);
	a = v3dot(r->direction, r->direction);
	b = 2.0f * v3dot(r->direction, l);
	c = v3dot(l, l) - ((s->diameter / 2.0f) * (s->diameter / 2.0f));
	sol = v3solve_quad(a, b, c);
	if (sol.x == 0.0f || sol.y < 0.001f || sol.z < 0.001f)
		return (0);
	h->distance = sol.y;
	return (1);
}

/*
 * check if a ray hits a sphere
 * returns 1 if hit 0 if not
 * the intersection information is returned in a t_hit
 * also calculates intersect point, normal and reflection
 */
int	sphere_hit(t_ray *r, t_hit *h, t_obj *s)
{
	if (!sphere_hit_quick(r, h, s))
		return (0);
	h->point = v3add(v3scale(r->direction, h->distance), r->origin);
	h->normal = v3norm(v3sub(h->point, s->coordinate));
	h->reflect = v3reflect(r->direction, h->normal);
	h->u = (1.0f + atan2(h->normal.y, h->normal.x) / M_PI) * 0.5f;
	h->v = acosf(h->normal.z) / M_PI;
	return (1);
}
