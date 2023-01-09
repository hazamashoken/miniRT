/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_convert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:04:04 by abossel           #+#    #+#             */
/*   Updated: 2023/01/09 16:48:43 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
#include "vector.h"
#include "mlx_render.h"
#include "minirt_define.h"

t_v3    rgbtov3(t_rgb trgb)
{
    t_v3    vrgb;

    vrgb.r = trgb[0];
    vrgb.g = trgb[1];
    vrgb.b = trgb[2];
    return (vrgb);
}

int v3toirgb(t_v3 vrgb)
{
    vrgb = v3clamp(vrgb, 0.0f, 255.0f);
    return (rgb(vrgb.r, vrgb.g, vrgb.b));
}

t_v3    v4tov3(t_v4sd vector)
{
    t_v3    vector2;

    vector2.v[0] = vector[0];
    vector2.v[1] = vector[1];
    vector2.v[2] = vector[2];
    return (vector2);
}

t_v4sd  v3tov4(t_v3 vector)
{
    t_v4sd  vector2;

    vector2[0] = vector.v[0];
    vector2[1] = vector.v[1];
    vector2[2] = vector.v[2];
    return (vector2);
}