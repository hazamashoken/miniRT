/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magitute.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:03:17 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/30 11:39:20 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

/// @brief set magitute of the vector at index 3
/// @param v t_v4sd without magnitute
/// @return t_v4sd with magnitute
t_v4sd	set_magnitute(t_v4sd v)
{
	v[3] = sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2));
	return (v);
}

/// @brief cal the maginute of a t_v4sd vector
/// @param v t_v4sd
/// @return the magnitute of the vector
double	get_magnitute(t_v4sd v)
{
	return (sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2)));
}
