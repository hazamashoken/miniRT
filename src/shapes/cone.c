/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:19:57 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/12 13:49:52 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "raytrace.h"
#include "vector3.h"

int	cone_quick_hit(t_ray *r, t_hit *h, t_v3 t_centre, t_v3 t_direction, float t_radius, float height)
{
	t_v3	L;
	t_v3	Q;
	t_v3	S;
	float	k;
	// float	m;

	L = v3sub(r->origin, t_centre);
	k = t_radius / height;
	Q.v[0] = v3dot(r->direction, r->direction) - (1 + k * k) * pow(v3dot(r->direction, t_direction), 2);
	Q.v[1] = 2 * (v3dot(r->direction, L) - (1 + k * k) * v3dot(r->direction, t_direction) * v3dot(L, t_direction));
	Q.v[2] = v3dot(L, L) - (1 + k * k) * pow(v3dot(L, t_direction), 2);
	S = v3solve_quad(Q.v[0], Q.v[1], Q.v[2]);
	if (S.v[0] == 0.0f || S.v[1] < 0.01f || S.v[2] < 0.01f)
		return (0);
	h->distance = S.v[1];
	return (1);
}

//  C is the vertex of the cone
//  V is the axis vector
//  k is the tangent of half angle of the cone
//  minm, maxm define cap points
int	cone_hit(t_ray *r, t_hit *h, t_v3 c_centre, t_v3 c_direction, float c_radius, float c_height)
{
	int     hit;
	float	m;
	t_v3	L;
	t_v3	P;
	float	k;
	float	limit;
	float	mag;

	hit = 0;
	if (v3dot(c_direction, r->direction) >= 0.0f
		&& disk_hit(r, h, v3sub(c_centre, v3scale(c_direction, c_height)), v3neg(c_direction), c_radius))
			hit = 1;
	// else if (v3dot(v3neg(c_direction), r->direction) < 0.0f
	// 	&& disk_hit(r, h, v3sub(c_centre, vhh), v3neg(c_direction), c_radius))
	// 		hit = 1;
	else if (cone_quick_hit(r, h, c_centre, c_direction, c_radius, c_height))
	{
		L = v3sub(r->origin, c_centre);
		h->point = v3add(v3scale(r->direction, h->distance), r->origin);
		P = v3sub(h->point, c_centre);
		m = v3dot(r->direction, c_direction) * h->distance + v3dot(L, c_direction);
		k = c_radius / c_height;
		mag = v3mag(P);
		limit = sqrt(c_height * c_height + c_radius * c_radius);
		// printf("%f\n", v3dot(v3norm(P), c_direction));
		if (mag <= limit && v3dot(v3norm(P), c_direction) <= 0.0f)
		{
			h->normal = v3norm(v3sub(v3sub(h->point, c_centre), v3scale(c_direction, -(1 + k * k * m))));
			h->reflect = v3reflect(r->direction, h->normal);
			hit = 1;
		}
	}
	return (hit);
}
