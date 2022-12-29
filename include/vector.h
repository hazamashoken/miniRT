/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:52:57 by tliangso          #+#    #+#             */
/*   Updated: 2022/12/29 16:58:03 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

typedef double	t_v4si __attribute__ ((vector_size (32)));

t_v4si	normalize(t_v4si v);
t_v4si	magnitute(t_v4si v);
t_v4si	cross(t_v4si v1, t_v4si v2);

#endif
