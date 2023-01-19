/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_rotate2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:25:36 by abossel           #+#    #+#             */
/*   Updated: 2023/01/19 11:18:42 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include <math.h>

/*
 * rotate a vector to dst direction relative to src direction
 */
t_v3	v3rot_rel(t_v3 vector, t_v3 src_direction, t_v3 dst_direction)
{
	t_v3	axis;
	float	angle;

	axis = v3norm(v3cross(src_direction, dst_direction));
	angle = acos(v3dot(src_direction, dst_direction));
	return (v3rot_axis(vector, axis, angle));
}
