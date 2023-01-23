/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_set_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:44:42 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/23 15:44:30 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector3.h"
#include "params.h"

/// @brief append a new shape to the shape struct arr
/// @param shape (shape struct *)
/// @param params (splited line)
/// @param flag (See minirt_define.h)
/// @return exit code
static int	set_shape(t_obj ***shape, char **params, int type, int flag)
{
	t_obj	*new;
	int		i;

	i = 0;
	new = (t_obj *)malloc(sizeof(t_obj));
	if (new == NULL)
		return (MALLOC_FAIL);
	if ((flag & F_COOR) == F_COOR)
		set_v3(ft_split(params[++i], ','), &new->coordinate);
	if ((flag & F_ORIEN) == F_ORIEN)
		set_vector(ft_split(params[++i], ','), &new->orientation);
	if ((flag & F_DIA) == F_DIA)
		new->diameter = ft_atod(params[++i]);
	if ((flag & F_HEI) == F_HEI)
		new->height = ft_atod(params[++i]);
	if ((flag & F_RGB) == F_RGB)
		set_v3(ft_split(params[++i], ','), &new->rgb);
	if ((flag & F_MAT) == F_MAT)
		set_material(new, params, ++i, flag);
	new->type = type;
	*shape = (t_obj **)nta_add_back((void **)*shape, new);
	if (*shape == NULL)
		return (MALLOC_FAIL);
	return (EXIT_SUCCESS);
}

/// @brief set the light struct
/// @param light (light struct *)
/// @param params (splited line)
/// @return exit code
static int	set_light(t_obj ***light, char **params)
{
	t_obj	*new;

	new = (t_obj *)malloc(sizeof(t_obj));
	if (new == NULL)
		return (MALLOC_FAIL);
	set_v3(ft_split(params[1], ','), &new->coordinate);
	new->brightness = ft_atod(params[2]);
	set_v3(ft_split(params[3], ','), &new->rgb);
	*light = (t_obj **)nta_add_back((void **)*light, new);
	if (*light == NULL)
		return (MALLOC_FAIL);
	return (EXIT_SUCCESS);
}

/// @brief set the env with params
/// @param params (splited line)
/// @param arg (struct to set the params)
/// @param type (See minirt_define.h)
/// @param flag (See minirt_define.h)
/// @return exit code
static int	set_env(char **params, void *arg, int type, int flag)
{
	if (check_params(params, type, flag))
		return (nta_free((void **)params), exit_err("Bad params", NULL), 1);
	else if (type == T_AMB)
	{
		((t_obj *)arg)->brightness = ft_atod(params[1]);
		set_v3(ft_split(params[2], ','), &((t_obj *)arg)->rgb);
	}
	else if (type == T_CAM)
	{
		set_v3(ft_split(params[1], ','), &((t_obj *)arg)->coordinate);
		set_vector(ft_split(params[2], ','), &((t_obj *)arg)->orientation);
		((t_obj *)arg)->fov = ft_atod(params[3]);
	}
	else if (type == T_LIGHT)
	{
		if (set_light((t_obj ***)arg, params))
			return (MALLOC_FAIL);
	}
	else if (type > T_SHAPE)
	{
		if (set_shape((t_obj ***)arg, params, type, flag))
			return (MALLOC_FAIL);
	}
	nta_free((void **)params);
	return (EXIT_SUCCESS);
}

// void	print_params(char **arg)
// {
// 	int i = 0;

// 	while (arg[i])
// 		printf("%s\n", arg[i++]);
// }

/// @brief build the params line by line
/// @param line (line from .rt file)
/// @param env (main struct)
/// @return error code 0 OK, 1 MALLOC ERR, 2 BAD ARG
static int	build_params(char *line, t_env *env)
{
	char	**params;

	params = ft_split_str(line, " \t\n");
	if (ft_strncmp(params[0], "A", 2) == 0)
		return (set_env(params, &env->amb, T_AMB, F_BRI | F_RGB));
	else if (ft_strncmp(params[0], "C", 2) == 0)
		return (set_env(params, &env->cam, T_CAM, F_COOR | F_ORIEN | F_FOV));
	else if (ft_strncmp(params[0], "L", 2) == 0)
		return (set_env(params, &env->light, T_LIGHT, F_COOR | F_BRI | F_RGB));
	else if (ft_strncmp(params[0], "pl", 3) == 0)
		return (set_env(params, &env->shape, T_PLANE, F_COOR
				| F_ORIEN | F_RGB | F_MAT));
	else if (ft_strncmp(params[0], "sp", 3) == 0)
		return (set_env(params, &env->shape, T_SPHERE, F_COOR
				| F_DIA | F_RGB | F_MAT));
	else if (ft_strncmp(params[0], "cy", 3) == 0)
		return (set_env(params, &env->shape, T_CYLINDER, F_COOR | F_ORIEN
				| F_DIA | F_HEI | F_RGB | F_MAT));
	else if (ft_strncmp(params[0], "co", 3) == 0)
		return (set_env(params, &env->shape, T_CONE, F_COOR | F_ORIEN
				| F_DIA | F_HEI | F_RGB | F_MAT));
	put_err("Error\nminirt: unknown type: ", params[0]);
	return (BAD_ARGUMENTS);
}

/// @brief set the params line by line
/// @param fd (fd of the open file)
/// @param env (main struct)
void	set_params(int fd, t_env *env)
{
	char	*line;
	int		error;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n' || line[0] == '#')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		error = build_params(line, env);
		free(line);
		if (error == MALLOC_FAIL)
			return (free_env(env), exit_perr("Error\nminirt"));
		else if (error == BAD_ARGUMENTS)
			return (free_env(env),
				exit_err("Error\nminirt: bad arguments", NULL));
		line = get_next_line(fd);
	}
	close(fd);
}
