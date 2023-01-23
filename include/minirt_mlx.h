/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_mlx.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 22:53:24 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/23 15:07:00 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_MLX_H
# define MINIRT_MLX_H

# include "mlx_render.h"

# ifdef __linux__
#  include "../minilibx-linux/mlx.h"
#  include "mlx_key_linux.h"
# else
#  include "../libmlx/mlx.h"
#  include "mlx_key_macos.h"

void	mlx_destroy_display(void *mlx);
# endif

void	move_camera(t_app *app, float dx, float dy, float dz);
void	rotate_camera(t_app *app, float dx, float dz);
int		destroy(t_app *app);
void	*change_obj(void	*data, int *index);

#endif
