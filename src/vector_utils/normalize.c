/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:52:40 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/30 11:39:44 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"


/// @brief normalized the vector t_v4sd
/// @param v
/// @return normalized vector t_v4sd
t_v4sd	normalize(t_v4sd v)
{
	v = set_magnitute(v);
	return ((t_v4sd){
		v[0] / v[3],
		v[1] / v[3],
		v[2] / v[3],
		1.0});
}
