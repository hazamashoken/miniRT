/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_mlx.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:53:24 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/08 23:11:11 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MLX_H
# define MINIRT_MLX_H

# ifdef __linux__
#  include <mlx.h>
#  include "mlx_key_linux.h"
# else
#  include "mlx.h"
#  include "mlx_key_macos.h"
# endif

# include "mlx_render.h"

#endif
