/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:19:57 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/22 21:59:06 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "raytrace.h"
#include "vector3.h"

int	cone_quick_hit(t_ray *r, t_hit *h, t_v3 t_centre, t_v3 t_direction, float t_radius, float height)
{
	t_v3	co;
	t_v3	q;
	float	rdcd;
	float	cocd;
	float	k;

	co = v3sub(r->origin, t_centre);
	rdcd = v3dot(r->direction, t_direction);
	cocd = v3dot(co, t_direction);
	k = t_radius / height;
	q.v[0] = v3dot(r->direction, r->direction) - (1.0f + k * k) * rdcd * rdcd;
	q.v[1] = 2.0f * (v3dot(r->direction, co) - (1.0f + k * k) * rdcd * cocd);
	q.v[2] = v3dot(co, co) - (1.0f + k * k) * cocd * cocd;
	q = v3solve_quad(q.v[0], q.v[1], q.v[2]);
	if (q.v[0] == 0.0f || (q.v[1] < 0.01f && q.v[2] < 0.01f))
		return (0);
	h->distance = q.v[2];
	if (q.v[0] == 1.0f && q.v[1] < 0.01f && q.v[2] >= 0.01f)
		return (1);
	h->point = v3add(v3scale(r->direction, h->distance), r->origin);
	if (!v3facing(t_centre, t_direction, h->point))
		return (1);
	h->distance = q.v[1];
	return (1);
}

/*
 * set the cylinder texture coordinates
 * make a normal from the centre to the hit point to set u and v like a sphere
 */
void	cone_texture_uv(t_ray *r, t_hit *h, t_v3 c_centre, t_v3 c_direction)
{
	t_v3	normal;
	t_v3	axis;
	float	angle;

	axis = v3norm(v3cross(v3new(0.0f, 0.0f, 1.0f), c_direction));
	angle = acos(v3dot(v3new(0.0f, 0.0f, 1.0f), c_direction));
	normal = v3norm(v3sub(h->point, v3sub(c_centre, c_direction)));
	normal = v3rot_axis(normal, axis, -angle);
	h->u = (1.0f + atan2(normal.y, normal.x) / M_PI) * 0.5f;
	h->v = acosf(normal.z) / M_PI;
}

int	cone_hit(t_ray *r, t_hit *h, t_v3 c_centre, t_v3 c_direction, float c_radius, float c_height)
{
	int		hit;
	float	m;
	float	k;
	t_v3	co;
	t_v3	cp;

	hit = 0;
	if (v3dot(c_direction, r->direction) >= 0.0f
		&& disk_hit(r, h, v3sub(c_centre, v3scale(c_direction, c_height)), v3neg(c_direction), c_radius))
			hit = 1;
	else if (cone_quick_hit(r, h, c_centre, c_direction, c_radius, c_height))
	{
		co = v3sub(r->origin, c_centre);
		h->point = v3add(v3scale(r->direction, h->distance), r->origin);
		cp = v3sub(h->point, c_centre);
		m = v3dot(r->direction, c_direction) * h->distance + v3dot(co, c_direction);
		k = c_radius / c_height;
		if (v3mag(cp) <= sqrt(c_height * c_height + c_radius * c_radius)
			&& v3dot(v3norm(cp), c_direction) <= 0.0f)
		{
			h->normal = v3norm(v3sub(cp, v3scale(c_direction, ((1.0f + k * k) * m))));
			h->reflect = v3reflect(r->direction, h->normal);
			hit = 1;
		}
	}
	if (hit)
		cone_texture_uv(r, h, c_centre, c_direction);
	return (hit);
}
