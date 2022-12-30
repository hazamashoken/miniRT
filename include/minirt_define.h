/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_define.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 11:40:15 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/30 12:22:35 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_DEFINE_H
# define MINIRT_DEFINE_H

typedef char	t_rgb __attribute__ ((vector_size (16)));

enum e_type
{
	T_CAM,
	T_AMB,
	T_LIGHT,
	T_SHAPE,
	T_PLANE,
	T_SPHERE,
	T_CYLINDER,
	T_CUBE,
	T_REGTANGLE,
	T_CONE,
};

enum e_flag
{
	F_COOR = 1,
	F_ORIEN = 2,
	F_DIA = 4,
	F_HEI = 8,
	F_RGB = 16,
	F_BRI = 32,
	F_FOV = 64,
	F_ALL = 255
};

enum e_error
{
	MALLOC_FAIL = 1,
	BAD_ARGUMENTS = 2
};

#endif
