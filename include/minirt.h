/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:46:16 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/04 20:03:56 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>

# include "vector.h"
# include "libft.h"
# include "nta.h"
# include "minirt_define.h"
# include "mlx_render.h"

typedef struct s_shape
{
	int		type;
	t_v4sd	coordinate;
	t_v4sd	orientation;
	double	diameter;
	double	height;
	t_rgb	rgb;
}	t_shape;

typedef struct s_light
{
	t_v4sd	coordinate;
	double	brightness;
	t_rgb	rgb;
}	t_light;

typedef struct s_cam
{
	t_v4sd	corrdinate;
	t_v4sd	orientation;
	double	fov;
}	t_cam;

typedef struct s_amb
{
	double	brightness;
	t_rgb	rgb;
}	t_amb;


typedef struct s_env
{
	t_cam	cam;
	t_amb	amb;
	t_light	**light;
	t_shape	**shape;
}	t_env;

/// @brief utils
/// @brief write str and arg to STDERR_FILENO
/// @param str (error message)
/// @param arg (NULLABLE if N.A)
/// @return error signal of 1
int		put_err(char *str, char *arg);

/// @brief utils
/// @brief write str and arg to STDERR_FILENO then exit
/// @param str (error message)
/// @param arg (NULLABLE if N.A)
void	exit_err(char *str, char *arg);

/// @brief utils
/// @brief perror str then exit
/// @param str (error message)
void	exit_perr(char *str);

/// @brief utils
/// @brief set the params of minirt
/// @param file (file path)
/// @param env (main struct)
void	params(char *file, t_env *env);



#endif
