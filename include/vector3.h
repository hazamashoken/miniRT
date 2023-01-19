/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 22:43:01 by abossel           #+#    #+#             */
/*   Updated: 2023/01/19 11:17:35 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_H
# define VECTOR3_H

# include "minirt.h"

t_v3	v3new(float x, float y, float z);
t_v3	v3neg(t_v3 vector);
t_v3	v3add(t_v3 vector1, t_v3 vector2);
t_v3	v3sub(t_v3 vector1, t_v3 vector2);

float	v3mag(t_v3 vector);
t_v3	v3scale(t_v3 vector, float scale);
t_v3	v3norm(t_v3 vector);
float	v3dot(t_v3 vector1, t_v3 vector2);
t_v3	v3cross(t_v3 vector1, t_v3 vector2);

t_v3	v3rotx(t_v3 vector, float radians);
t_v3	v3roty(t_v3 vector, float radians);
t_v3	v3rotz(t_v3 vector, float radians);
t_v3	v3rotxyz(t_v3 vector, float rad_x, float rad_y, float rad_z);
t_v3	v3rot_axis(t_v3 vector, t_v3 axis, float radians);

t_v3	v3rot_rel(t_v3 vector, t_v3 src_direction, t_v3 dst_direction);

float	norm_rad(float radians);
float	norm_deg(float degrees);
float	deg2rad(float degrees);
float	rad2deg(float radians);

t_v3	v3zero(void);
t_v3	v3unitx(void);
t_v3	v3unity(void);
t_v3	v3unitz(void);

t_v3	v3solve_quad(float a, float b, float c);
float	clamp(float n, float min, float max);
t_v3	v3clamp(t_v3 vector, float min, float max);
t_v3	v3reflect(t_v3 direction, t_v3 normal);

int		v3toirgb(t_v3 vrgb);

// t_v3	rgbtov3(t_rgb trgb);
// int		v3toirgb(t_v3 vrgb);
// t_v3	v4tov3(t_v4sd vector); (deprecated)
// t_v4sd	v3tov4(t_v3 vector); (deprecated)

#endif
