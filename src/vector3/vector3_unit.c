/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_unit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:36:59 by abossel           #+#    #+#             */
/*   Updated: 2023/01/15 10:42:39 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

/*
 * returns a zero vector
 */
t_v3    v3zero()
{
    return (v3new(0.0f, 0.0f, 0.0f));
}

/*
 * returns unit vector on the x axis
 */
t_v3    v3unitx()
{
    return (v3new(1.0f, 0.0f, 0.0f));
}

/*
 * returns unit vector on the y axis
 */
t_v3    v3unity()
{
    return (v3new(0.0f, 1.0f, 0.0f));
}

/*
 * returns unit vector on the z axis
 */
t_v3    v3unitz()
{
    return (v3new(0.0f, 0.0f, 1.0f));
}