/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 10:53:24 by abossel           #+#    #+#             */
/*   Updated: 2023/01/05 23:43:08 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

/*
 * check if a ray hits a sphere
 * returns the intersection information in a t_hit
 * t_hit.distance is -1 if no intersection
 */
t_hit	sphere_hit(t_ray r, t_v3 s_centre, float s_radius)
{
	t_v3	L;
	t_v3	Q;
	t_v3	sol;
	t_hit	h;

	L = v3sub(r.origin, s_centre);
	Q.a = v3dot(r.direction, r.direction);
	Q.b = 2.0f * v3dot(r.direction, L);
	Q.c = v3dot(L, L) - (s_radius * s_radius);
	sol = v3solve_quad(Q.a, Q.b, Q.c);
	if (sol.a == 0.0f || sol.b < 0.0f || sol.c < 0.0f)
		h.distance = -1.0f;
	else
	{
		h.distance = sol.b;
		h.point = v3add(v3scale(r.direction, h.distance), r.origin);
		h.normal = v3norm(v3sub(h.point, s_centre));
	}
	return (h);
}