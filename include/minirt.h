/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:46:16 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/13 12:39:43 by tliangso         ###   ########.fr       */
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

// # include "vector.h"
# include "libft.h"
# include "nta.h"
# include "minirt_define.h"
# include "mlx_render.h"

typedef union u_v3
{
	struct
	{
		float	r;
		float	g;
		float	b;
	};
	struct
	{
		float	x;
		float	y;
		float	z;
	};
	float	v[3];
}	t_v3;

typedef struct s_obj
{
	int		type;
	t_v3	coordinate;
	t_v3	orientation;
	double	diameter;
	double	height;
	t_v3	rgb;
	char	material[1024];
	double	fov;
	double	brightness;
}	t_obj;

// typedef struct s_light
// {
// 	t_v3	coordinate;
// 	double	brightness;
// 	t_v3	rgb;
// }	t_light;

// typedef struct s_cam
// {
// 	t_v3	coordinate;
// 	t_v3	orientation;
// }	t_cam;

// typedef struct s_amb
// {
// 	t_v3	rgb;
// }	t_amb;

typedef struct s_env
{
	t_obj	cam;
	t_obj	amb;
	t_obj	**light;
	t_obj	**shape;
	int		light_count;
	int		shape_count;
	t_obj	*cur_obj;
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

/// @brief utils
/// @brief free the params of minirt
/// @param env (main struct)
void	free_env(t_env *env);

/// @brief init env with 0 or NULL as default
/// @param env (main struct)
void	init_env(t_env *env);

/// @brief set char **rgb values then nta_free the values
/// @param values (string of rgb)
/// @return t_rgb type vector
void	set_v3(char **values, t_v3 *v3);

/// @brief set t_v4sd then free nta_free the values
/// @param values
/// @return t_v4sd vector with magnitute
void	set_vector(char **values, t_v3 *vector);

/// @brief check file extension and return the fd if file path can be open()
/// @param file (file path)
/// @return fd of the opened file
int		check_file(char *file);

/// @brief set the params line by line
/// @param fd (fd of the open file)
/// @param env (main struct)
void	set_params(int fd, t_env *env);

#endif
