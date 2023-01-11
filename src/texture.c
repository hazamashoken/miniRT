/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:48:41 by abossel           #+#    #+#             */
/*   Updated: 2023/01/11 12:51:53 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "raytrace.h"
#include "vector3.h"

/*
 * check if a point is on a black checkerboard square
 * only for shapes that have texture coordinates
 */
int	checkerboard_black(t_hit *h, float scale)
{
	if (fmodf(h->u * scale, 1.0f) > 0.5f
		^ fmodf(h->v * scale, 1.0f) > 0.5f)
		return (1);
	return (0);
}