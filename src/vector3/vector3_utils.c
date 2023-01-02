/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 12:05:54 by abossel           #+#    #+#             */
/*   Updated: 2022/12/30 13:05:47 by abossel          ###   ########.fr       */
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
