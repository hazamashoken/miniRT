/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_multiply.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 23:03:07 by abossel           #+#    #+#             */
/*   Updated: 2022/12/30 01:30:39 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include <math.h>

float	v3mag(t_v3 vector)
{
	vector.v[0] *= vector.v[0];
	vector.v[1] *= vector.v[1];
	vector.v[2] *= vector.v[2];
	return (sqrt(vector.v[0] + vector.v[1] + vector.v[2]));
}

t_v3	v3scale(t_v3 vector, float scale)
{
	vector.v[0] *= scale;
	vector.v[1] *= scale;
	vector.v[2] *= scale;
	return (vector);
}

t_v3	v3norm(t_v3 vector)
{
	t_v3	vector2;
	float	scale;

	vector2.v[0] = vector.v[0] * vector.v[0];
	vector2.v[1] = vector.v[1] * vector.v[1];
	vector2.v[2] = vector.v[2] * vector.v[2];
	scale = sqrt(vector2.v[0] + vector2.v[1] + vector2.v[2]);
	vector.v[0] /= scale;
	vector.v[1] /= scale;
	vector.v[2] /= scale;
	return (vector);
}

float	v3dot(t_v3 vector1, t_v3 vector2)
{
	vector1.v[0] *= vector2.v[0];
	vector1.v[1] *= vector2.v[1];
	vector1.v[2] *= vector2.v[2];
	return (vector1.v[0] + vector1.v[1] + vector1.v[2]);
}

t_v3	v3cross(t_v3 vector1, t_v3 vector2)
{
	t_v3	vector3;

	vector3.v[0] = vector1.v[1] * vector2.v[2] - vector1.v[2] * vector2.v[1];
	vector3.v[1] = vector1.v[2] * vector2.v[0] - vector1.v[0] * vector2.v[2];
	vector3.v[2] = vector1.v[0] * vector2.v[1] - vector1.v[1] * vector2.v[0];
	return (vector3);
}
