/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:41:32 by abossel           #+#    #+#             */
/*   Updated: 2023/01/23 14:06:44 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "raytrace.h"
#include "vector3.h"

int	tube_hit_quick(t_ray *r, t_hit *h, t_obj *s)
{
	t_v3	co;
	t_v3	q;
	float	t1;
	float	t2;

	co = v3sub(r->origin, s->coordinate);
	t1 = v3dot(r->direction, s->orientation);
	t2 = v3dot(co, s->orientation);
	q.v[0] = v3dot(r->direction, r->direction) - t1 * t1;
	q.v[1] = 2.0f * (v3dot(r->direction, co) - t1 * t2);
	q.v[2] = v3dot(co, co) - t2 * t2 - (s->diameter * s->diameter / 4.0f);
	q = v3solve_quad(q.v[0], q.v[1], q.v[2]);
	if (q.v[0] == 0.0f || q.v[1] < 0.01f || q.v[2] < 0.01f)
		return (0);
	h->distance = q.v[1];
	return (1);
}

int	tube_hit(t_ray *r, t_hit *h, t_obj *s)
{
	t_v3	co;
	float	m;

	if (!tube_hit_quick(r, h, s))
		return (0);
	h->point = v3add(v3scale(r->direction, h->distance), r->origin);
	co = v3sub(r->origin, s->coordinate);
	m = v3dot(r->direction, s->orientation)
		* h->distance + v3dot(co, s->orientation);
	h->normal = v3norm(v3sub(v3sub(h->point, s->coordinate),
				v3scale(s->orientation, m)));
	h->reflect = v3reflect(r->direction, h->normal);
	return (1);
}

/*
 * set the cylinder texture coordinates
 * make a normal from the centre to the hit point to set u and v like a sphere
 */
void	cylinder_texture_uv(t_hit *h, t_v3 c_direction)
{
	t_v3	normal;
	t_v3	axis;
	float	angle;

	axis = v3norm(v3cross(v3new(0.0f, 0.0f, 1.0f), c_direction));
	angle = acos(v3dot(v3new(0.0f, 0.0f, 1.0f), c_direction));
	normal = v3norm(v3sub(h->point, c_direction));
	normal = v3rot_axis(normal, axis, -angle);
	h->u = (1.0f + atan2(normal.y, normal.x) / M_PI) * 0.5f;
	h->v = acosf(normal.z) / M_PI;
}

int	cylinder_disk_hit(t_ray *r, t_hit *h, t_obj *s)
{
	t_obj	disk;
	float	hh;
	t_v3	vhh;

	disk.type = T_PLANE;
	disk.diameter = s->diameter;
	hh = s->height / 2.0f;
	vhh = v3scale(s->orientation, hh);
	if (v3dot(s->orientation, r->direction) < 0.0f)
	{
		disk.coordinate = v3add(s->coordinate, vhh);
		disk.orientation = s->orientation;
		if (disk_hit(r, h, &disk))
			return (1);
	}
	if (v3dot(v3neg(s->orientation), r->direction) < 0.0f)
	{
		disk.coordinate = v3sub(s->coordinate, vhh);
		disk.orientation = v3neg(s->orientation);
		if (disk_hit(r, h, &disk))
			return (1);
	}
	return (0);
}

int	cylinder_hit(t_ray *r, t_hit *h, t_obj *s)
{
	float	limit2;
	float	hh;
	t_v3	vpoint;
	int		hit;

	hit = 0;
	hh = s->height / 2.0f;
	if (cylinder_disk_hit(r, h, s))
			hit = 1;
	else if (tube_hit(r, h, s))
	{
		limit2 = (s->diameter * s->diameter / 4.0f) + hh * hh;
		vpoint = v3sub(h->point, s->coordinate);
		if (v3dot(vpoint, vpoint) <= limit2)
			hit = 1;
	}
	if (hit)
		cylinder_texture_uv(h, s->orientation);
	return (hit);
}
