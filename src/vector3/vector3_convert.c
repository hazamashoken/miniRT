/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_convert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 21:04:04 by abossel           #+#    #+#             */
/*   Updated: 2023/01/11 21:36:46 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"
// #include "vector.h"
#include "mlx_render.h"
#include "minirt_define.h"

t_v3	rgbtov3(t_rgb trgb)
{
	t_v3	vrgb;

	vrgb.r = (unsigned char)trgb[0];
	vrgb.g = (unsigned char)trgb[1];
	vrgb.b = (unsigned char)trgb[2];
	return (vrgb);
}

t_v3	irgbtov3(int irgb)
{
	t_v3	colour;

	colour.r = get_r(irgb);
	colour.g = get_g(irgb);
	colour.b = get_b(irgb);
	return (colour);
}

int	v3toirgb(t_v3 vrgb)
{
	vrgb = v3clamp(vrgb, 0.0f, 255.0f);
	return (rgb(vrgb.r, vrgb.g, vrgb.b));
}

// t_v3    v4tov3(t_v4sd vector)
// {
//     t_v3    vector2;

//     vector2.v[0] = vector[0];
//     vector2.v[1] = vector[1];
//     vector2.v[2] = vector[2];
//     return (vector2);
// }

// t_v4sd  v3tov4(t_v3 vector)
// {
//     t_v4sd  vector2;

//     vector2[0] = vector.v[0];
//     vector2[1] = vector.v[1];
//     vector2[2] = vector.v[2];
//     return (vector2);
// }
