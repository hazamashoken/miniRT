/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_translate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 22:43:07 by abossel           #+#    #+#             */
/*   Updated: 2022/12/30 00:23:49 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_v3	v3new(float x, float y, float z)
{
	t_v3	vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_v3	v3neg(t_v3 vector)
{
	vector.v[0] = -vector.v[0];
	vector.v[1] = -vector.v[1];
	vector.v[2] = -vector.v[2];
	return (vector);
}

t_v3	v3add(t_v3 vector1, t_v3 vector2)
{
	vector1.v[0] += vector2.v[0];
	vector1.v[1] += vector2.v[1];
	vector1.v[2] += vector2.v[2];
	return (vector1);
}

t_v3	v3sub(t_v3 vector1, t_v3 vector2)
{
	vector1.v[0] -= vector2.v[0];
	vector1.v[1] -= vector2.v[1];
	vector1.v[2] -= vector2.v[2];
	return (vector1);
}
