/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:52:57 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/30 11:48:19 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

typedef double	t_v4sd __attribute__ ((vector_size (32)));

/// @brief normalized the vector t_v4sd
/// @param v
/// @return normalized vector t_v4sd
t_v4sd	normalize(t_v4sd v);

/// @brief set magitute of the vector at index 3
/// @param v t_v4sd without magnitute
/// @return t_v4sd with magnitute
t_v4sd	set_magnitute(t_v4sd v);

/// @brief cal the maginute of a t_v4sd vector
/// @param v t_v4sd
/// @return the magnitute of the vector
double	get_magnitute(t_v4sd v);

/// @brief do cross product between v1 and v2
/// @param v1
/// @param v2
/// @return t_v4sd
t_v4sd	cross(t_v4sd v1, t_v4sd v2);

#endif
