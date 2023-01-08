/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:05:54 by abossel           #+#    #+#             */
/*   Updated: 2023/01/08 19:33:00 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include <math.h>

/*
 * solves a quadratic equation
 * solves ax^2 + bx + c and returns the solution as a vector
 * x is 1 if a real solution is found or 0 if not
 * y and z are the solutions to the equation
 */
t_v3	v3solve_quad(float a, float b, float c)
{
	float	disc;
	float	q;
	float	x0;
	float	x1;

	disc = b * b - 4.0f * a * c;
	if (disc < 0.0f)
		return (v3new(0.0f, 0.0f, 0.0f));
	if (disc == 0.0f)
	{
		x0 = -0.5f * b / a;
		x1 = x0;
		return (v3new(1.0f, x0, x1));
	}
	if (b > 0.0f)
		q = -0.5 * (b + sqrt(disc));
	else
		q = -0.5 * (b - sqrt(disc));
	x0 = q / a;
	x1 = c / q;
	if (x0 > x1)
		return (v3new(1.0f, x1, x0));
	return (v3new(1.0f, x0, x1));
}

float	clamp(float n, float min, float max)
{
	if (n < min)
		n = min;
	else if (n > max)
		n = max;
	return (n);
}

/*
 * clamp vector between min and max
 */
t_v3	v3clamp(t_v3 vector, float min, float max)
{
	if (vector.v[0] < min)
		vector.v[0] = min;
	else if (vector.v[0] > max)
		vector.v[0] = max;
	if (vector.v[1] < min)
		vector.v[1] = min;
	else if (vector.v[1] > max)
		vector.v[1] = max;
	if (vector.v[2] < min)
		vector.v[2] = min;
	else if (vector.v[2] > max)
		vector.v[2] = max;
	return (vector);
}

/*
 * returns the reflection vector
 * r = d - (2 * d . n) * n
 * direction is the vector pointing at the surface
 * normal is the normal vector of the surface
 * normal must be normalized
 */
t_v3	v3reflect(t_v3 direction, t_v3 normal)
{
	return (v3sub(direction, v3scale(normal, 2.0f * v3dot(direction, normal))));
}