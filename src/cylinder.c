/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:41:32 by abossel           #+#    #+#             */
/*   Updated: 2023/01/09 22:16:07 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "raytrace.h"
#include "vector3.h"

int	disk_hit(t_ray *r, t_hit *h, t_v3 d_centre, t_v3 d_normal, float d_radius)
{
    t_v3    rv;

    if (plane_hit(r, h, d_centre, d_normal))
    {
        rv = v3sub(h->point, d_centre);
        if (v3dot(rv, rv) <= d_radius * d_radius)
            return (1);
    }
	return (0);
}

int	tube_hit_quick(t_ray *r, t_hit *h, t_v3 t_centre, t_v3 t_direction, float t_radius)
{
    t_v3    L;
    t_v3    Q;
    t_v3    S;
    float   t1;
    float   t2;

    L = v3sub(r->origin, t_centre);
    t1 = v3dot(r->direction, t_direction);
    t2 = v3dot(L, t_direction);
    Q.v[0] = v3dot(r->direction, r->direction) - t1 * t1;
    Q.v[1] = 2.0f * (v3dot(r->direction, L) - t1 * t2);
    Q.v[2] = v3dot(L, L) - t2 * t2 - t_radius * t_radius;
    S = v3solve_quad(Q.v[0], Q.v[1], Q.v[2]);
	if (S.v[0] == 0.0f || S.v[1] < 0.001f || S.v[2] < 0.001f)
		return (0);
    h->distance = S.v[1];
	return (1);
}

int	tube_hit(t_ray *r, t_hit *h, t_v3 t_centre, t_v3 t_direction, float t_radius)
{
    t_v3    L;
    float   m;

    if (!tube_hit_quick(r, h, t_centre, t_direction, t_radius))
        return (0);
    h->point = v3add(v3scale(r->direction, h->distance), r->origin);
    L = v3sub(r->origin, t_centre);
    m = v3dot(r->direction, t_direction) * h->distance + v3dot(L, t_direction);
    h->normal = v3norm(v3sub(v3sub(h->point, t_centre), v3scale(t_direction, m)));
    h->reflect = v3reflect(r->direction, h->normal);
    return (1);
}

int	cylinder_hit(t_ray *r, t_hit *h, t_v3 c_centre, t_v3 c_direction, float c_radius, float c_height)
{
    float   limit2;
    float   hheight;
    t_v3    vpoint;

    if (v3dot(c_direction, r->direction) < 0.0f)
    {
        if (disk_hit(r, h, v3add(c_centre, v3scale(c_direction, c_height / 2.0f)), c_direction, c_radius))
            return (1);
    }
    if (v3dot(v3neg(c_direction), r->direction) < 0.0f)
    {
        if (disk_hit(r, h, v3sub(c_centre, v3scale(c_direction, c_height / 2.0f)), v3neg(c_direction), c_radius))
            return (1);
    }
    if (tube_hit(r, h, c_centre, c_direction, c_radius))
    {
        hheight = c_height / 2.0f;
        limit2 = c_radius * c_radius + hheight * hheight;
        vpoint = v3sub(h->point, c_centre);
        if (v3dot(vpoint, vpoint) <= limit2)
            return (1);
    }
    return (0);
}