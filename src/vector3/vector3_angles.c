/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_angles.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 10:07:33 by abossel           #+#    #+#             */
/*   Updated: 2022/12/30 10:41:21 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include <math.h>

float	norm_rad(float radians)
{
	float	two_pi;

	two_pi = M_PI * 2.0f;
	while (radians > M_PI)
		radians -= two_pi;
	while (radians < -M_PI)
		radians += two_pi;
	return (radians);
}

float	norm_deg(float degrees)
{
	while (degrees > 180.0f)
		degrees -= 360.0f;
	while (degrees < -180.0f)
		degrees += 360.0f;
	return (degrees);
}

float	deg2rad(float degrees)
{
	return (degrees * (M_PI / 180.0f));
}

float	rad2deg(float radians)
{
	return (radians * (180.0f / M_PI));
}
