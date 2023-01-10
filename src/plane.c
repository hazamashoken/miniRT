/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:59:41 by abossel           #+#    #+#             */
/*   Updated: 2023/01/10 10:19:03 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int	plane_hit_quick(t_ray *r, t_hit *h, t_v3 p_centre, t_v3 p_normal)
{
    float   denom;
    
    denom = v3dot(p_normal, r->direction);
    if (fabs(denom) > 0.001f)
        h->distance = v3dot(v3sub(p_centre, r->origin), p_normal) / denom;
    if (h->distance >= 0.001f)
        return (1);
	return (0);
}

int	plane_hit(t_ray *r, t_hit *h, t_v3 p_centre, t_v3 p_normal)
{
	if (!plane_hit_quick(r, h, p_centre, p_normal))
		return (0);
	h->point = v3add(v3scale(r->direction, h->distance), r->origin);
    h->normal = p_normal;
	return (1);
}