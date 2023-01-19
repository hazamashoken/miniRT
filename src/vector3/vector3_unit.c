/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_unit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:36:59 by abossel           #+#    #+#             */
/*   Updated: 2023/01/19 11:16:44 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

/*
 * returns a zero vector
 */
t_v3	v3zero(void)
{
	return (v3new(0.0f, 0.0f, 0.0f));
}

/*
 * returns unit vector on the x axis
 */
t_v3	v3unitx(void)
{
	return (v3new(1.0f, 0.0f, 0.0f));
}

/*
 * returns unit vector on the y axis
 */
t_v3	v3unity(void)
{
	return (v3new(0.0f, 1.0f, 0.0f));
}

/*
 * returns unit vector on the z axis
 */
t_v3	v3unitz(void)
{
	return (v3new(0.0f, 0.0f, 1.0f));
}
