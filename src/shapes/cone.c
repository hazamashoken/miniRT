/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 22:19:57 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/23 00:16:08 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "raytrace.h"
#include "vector3.h"

float	cone_choose_distance(t_ray *r, t_hit *h, t_obj *s, t_v3 q)
{
	t_v3	point1;
	t_v3	point2;
	int		facing1;
	int		facing2;

	if (q.v[1] < 0.01f && q.v[2] >= 0.01f)
		return (q.v[2]);
	point1 = v3add(v3scale(r->direction, q.v[1]), r->origin);
	point2 = v3add(v3scale(r->direction, q.v[2]), r->origin);
	facing1 = v3facing(s->coordinate, s->orientation, point1);
	facing2 = v3facing(s->coordinate, s->orientation, point2);
	if (facing1 ^ facing2)
		return (q.v[2]);
	return (q.v[1]);
}

int	cone_hit_quick(t_ray *r, t_hit *h, t_obj *s)
{
	t_v3	co;
	t_v3	q;
	float	rdcd;
	float	cocd;
	float	k;

	co = v3sub(r->origin, s->coordinate);
	rdcd = v3dot(r->direction, s->orientation);
	cocd = v3dot(co, s->orientation);
	k = s->diameter / 2.0f / s->height;
	q.v[0] = v3dot(r->direction, r->direction) - (1.0f + k * k) * rdcd * rdcd;
	q.v[1] = 2.0f * (v3dot(r->direction, co) - (1.0f + k * k) * rdcd * cocd);
	q.v[2] = v3dot(co, co) - (1.0f + k * k) * cocd * cocd;
	q = v3solve_quad(q.v[0], q.v[1], q.v[2]);
	if (q.v[0] == 0.0f || (q.v[1] < 0.01f && q.v[2] < 0.01f))
		return (0);
	h->distance = cone_choose_distance(r, h, s, q);
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

int	cone_disk_hit(t_ray *r, t_hit *h, t_obj *s)
{
	t_obj	disk;

	if (v3dot(s->orientation, r->direction) >= 0.0f)
	{
		disk.type = T_PLANE;
		disk.coordinate = v3sub(s->coordinate, v3scale(s->orientation,
			s->height));
		disk.orientation = v3neg(s->orientation);
		disk.diameter = s->diameter;
		if (disk_hit(r, h, &disk))
			return (1);
	}
	return (0);
}

int	cone_hit(t_ray *r, t_hit *h, t_obj *s)
{
	int		hit;
	float	m;
	t_v3	cp;

	hit = 0;
	if (cone_disk_hit(r, h, s))
			hit = 1;
	else if (cone_hit_quick(r, h, s))
	{
		h->point = v3add(v3scale(r->direction, h->distance), r->origin);
		cp = v3sub(h->point, s->coordinate);
		m = v3dot(r->direction, s->orientation) * h->distance
			+ v3dot(v3sub(r->origin, s->coordinate), s->orientation);
		if (v3mag(cp) <= hyp(s->height, s->diameter / 2.0f)
			&& v3dot(v3norm(cp), s->orientation) <= 0.0f)
		{
			h->normal = v3norm(v3sub(cp, v3scale(s->orientation,
					((1.0f + sqr(s->diameter / 2.0f / s->height)) * m))));
			h->reflect = v3reflect(r->direction, h->normal);
			hit = 1;
		}
	}
	if (hit)
		cone_texture_uv(r, h, s->coordinate, s->orientation);
	return (hit);
}
