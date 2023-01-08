/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 17:17:13 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/08 17:15:06 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/// @brief check file extension and return the fd if file path can be open()
/// @param file (file path)
/// @return fd of the opened file
static int	check_file(char *file)
{
	int	fd;

	if (ft_strrchr(file, '.') == NULL)
		exit_err("Error\nminirt: wrong file extension: ", file);
	if (ft_strncmp(ft_strrchr(file, '.'), ".rt", 4) != 0)
		exit_err("Error\nminirt: wrong file extension: ", file);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_perr("Error\nminirt");
	return (fd);
}

/// @brief set char **rgb values then nta_free the values
/// @param values (string of rgb)
/// @return t_rgb type vector
static t_rgb	set_rgb(char **values)
{
	t_rgb	rgb;

	rgb = (t_rgb){
		ft_atoi(values[0]),
		ft_atoi(values[1]),
		ft_atoi(values[2])
	};
	nta_free((void **)values);
	return (rgb);
}

/// @brief set t_v4sd then free nta_free the values
/// @param values
/// @return t_v4sd vector with magnitute
static t_v4sd	set_vector(char **values)
{
	t_v4sd	v;

	v = (t_v4sd){
		ft_atod(values[0]),
		ft_atod(values[1]),
		ft_atod(values[2]),
	};
	return (set_magnitute(v));
}

/// @brief append a new shape to the shape struct arr
/// @param shape (shape struct *)
/// @param params (splited line)
/// @param flag (See minirt_define.h)
/// @return exit code
static int	set_shape(t_shape ***shape, char **params, int type, int flag)
{
	t_shape	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(t_shape));
	if (new == NULL)
		return (MALLOC_FAIL);
	if ((flag & F_COOR) == F_COOR)
		new->coordinate = set_vector(ft_split(params[++i], ','));
	if ((flag & F_ORIEN) == F_ORIEN)
		new->orientation = set_vector(ft_split(params[++i], ','));
	if ((flag & F_DIA) == F_DIA)
		new->diameter = ft_atod(params[++i]);
	if ((flag & F_HEI) == F_HEI)
		new->height = ft_atod(params[++i]);
	if ((flag & F_RGB) == F_RGB)
		new->rgb = set_rgb(ft_split(params[++i], ','));
	new->type = type;
	*shape = (t_shape **)nta_add_back((void **)*shape, new);
	if (*shape == NULL)
		return (MALLOC_FAIL);
	return (EXIT_SUCCESS);
}

static int	set_light(t_light ***light, char **params)
{
	t_light	*new;

	new = malloc(sizeof(t_light));
	if (new == NULL)
		return (MALLOC_FAIL);
	new->coordinate = set_vector(ft_split(params[1], ','));
	new->brightness = ft_atod(params[2]);
	new->rgb = set_rgb(ft_split(params[3], ','));
	*light = (t_light **)nta_add_back((void **)*light, new);
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
	if (type == T_AMB)
	{
		((t_amb *)arg)->brightness = ft_atod(params[1]);
		((t_amb *)arg)->rgb = set_rgb(ft_split(params[2], ','));
	}
	else if (type == T_CAM)
	{
		((t_cam *)arg)->coordinate = set_vector(ft_split(params[1], ','));
		((t_cam *)arg)->orientation = set_vector(ft_split(params[2], ','));
		((t_cam *)arg)->fov = ft_atod(params[3]);
	}
	else if (type == T_LIGHT)
	{
		if (set_light((t_light ***)arg, params))
			return (MALLOC_FAIL);
	}
	else if (type == T_SPHERE || type == T_PLANE || type == T_CYLINDER)
	{
		if (set_shape((t_shape ***)arg, params, type, flag))
			return (MALLOC_FAIL);
	}
	else
		put_err("Error\nminirt: unknown type: ", params[0]);
	return (EXIT_SUCCESS);
}

static void print_params(char **arg)
{
	int i = 0;
	while (arg[i])
		printf("%s\n", arg[i++]);
}

/// @brief build the params line by line
/// @param line (line from .rt file)
/// @param env (main struct)
/// @return error code 0 OK, 1 MALLOC ERR, 2 BAD ARG
static int	build_params(char *line, t_env *env)
{
	char	**params;
	int		error;

	params = ft_split(line, '\t');
	print_params(params);
	if (ft_strncmp(params[0], "A", 2) == 0)
		error = set_env(params, &env->amb, T_AMB, F_BRI | F_RGB);
	else if (ft_strncmp(params[0], "C", 2) == 0)
		error = set_env(params, &env->cam, T_CAM, F_COOR | F_ORIEN | F_FOV);
	else if (ft_strncmp(params[0], "L", 2) == 0)
		error = set_env(params, &env->light, T_LIGHT, F_COOR | F_BRI | F_RGB);
	else if (ft_strncmp(params[0], "sp", 3) == 0)
		error = set_env(params, &env->shape, T_SPHERE, F_COOR | F_DIA | F_RGB);
	else if (ft_strncmp(params[0], "pl", 3) == 0)
		error = set_env(params, &env->shape, T_PLANE, F_COOR | F_ORIEN | F_RGB);
	else if (ft_strncmp(params[0], "cy", 3) == 0)
		error = set_env(params, &env->shape, T_CYLINDER, F_COOR | F_ORIEN
				| F_DIA | F_HEI | F_RGB);
	else
		error = BAD_ARGUMENTS;
	return (error);
}

void	free_env(t_env *env)
{
	if (env->light)
	{
		free(env->light);
		env->light = NULL;
	}
	if (env->shape)
	{
		free(env->shape);
		env->shape = NULL;
	}
}

/// @brief set the params line by line
/// @param fd (fd of the open file)
/// @param env (main struct)
static void	set_params(int fd, t_env *env)
{
	char	*line;
	int		error;

	line = get_next_line(fd);
	while (line)
	{
		error = build_params(line, env);
		if (error == MALLOC_FAIL)
		{
			free_env(env);
			free(line);
			exit_perr("Error\nminirt");
		}
		else if (error == BAD_ARGUMENTS)
		{
			free_env(env);
			free(line);
			exit_err("Error\nminirt: bad arguments", NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
}

/// @brief init env with 0 or NULL as default
/// @param env (main struct)
static void	init_env(t_env *env)
{
	env->cam.coordinate = (t_v4sd){0, 0, 0, 0};
	env->cam.fov = 0;
	env->cam.orientation = (t_v4sd){0, 0, 0, 0};
	env->amb.brightness = 0;
	env->amb.rgb = (t_rgb){0, 0, 0, 0};
	env->light = NULL;
	env->shape = NULL;
}

/// @brief set the params of minirt
/// @param file (file path)
/// @param env (main struct)
void	params(char *file, t_env *env)
{
	init_env(env);
	set_params(check_file(file), env);
	printf("%s\n", file);
}
