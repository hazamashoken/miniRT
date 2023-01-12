/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_set_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:44:42 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/12 12:17:27 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	new = (t_shape *)malloc(sizeof(t_shape));
	if (new == NULL)
		return (MALLOC_FAIL);
	if ((flag & F_COOR) == F_COOR)
		set_vector(ft_split(params[++i], ','), &new->coordinate);
	if ((flag & F_ORIEN) == F_ORIEN)
		set_vector(ft_split(params[++i], ','), &new->orientation);
	if ((flag & F_DIA) == F_DIA)
		new->diameter = ft_atod(params[++i]);
	if ((flag & F_HEI) == F_HEI)
		new->height = ft_atod(params[++i]);
	if ((flag & F_RGB) == F_RGB)
		set_rgb(ft_split(params[++i], ','), &new->rgb);
	new->type = type;
	*shape = (t_shape **)nta_add_back((void **)*shape, new);
	if (*shape == NULL)
		return (MALLOC_FAIL);
	printf("%d\n", nta_size((void **)*shape));
	return (EXIT_SUCCESS);
}

/// @brief set the light struct
/// @param light (light struct *)
/// @param params (splited line)
/// @return exit code
static int	set_light(t_light ***light, char **params)
{
	t_light	*new;

	new = (t_light *)malloc(sizeof(t_light));
	if (new == NULL)
		return (MALLOC_FAIL);
	set_vector(ft_split(params[1], ','), &new->coordinate);
	new->brightness = ft_atod(params[2]);
	set_rgb(ft_split(params[3], ','), &new->rgb);
	*light = (t_light **)nta_add_back((void **)*light, new);
	printf("%d\n", nta_size((void **)*light));
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
		set_rgb(ft_split(params[2], ','), &((t_amb *)arg)->rgb);
	}
	else if (type == T_CAM)
	{
		set_vector(ft_split(params[1], ','), &((t_cam *)arg)->coordinate);
		set_vector(ft_split(params[2], ','), &((t_cam *)arg)->orientation);
		((t_cam *)arg)->fov = ft_atod(params[3]);
	}
	else if (type == T_LIGHT)
	{
		if (set_light((t_light ***)arg, params))
			return (MALLOC_FAIL);
	}
	else if (type > T_SHAPE)
	{
		if (set_shape((t_shape ***)arg, params, type, flag))
			return (MALLOC_FAIL);
	}
	else
		put_err("Error\nminirt: unknown type: ", params[0]);
	return (EXIT_SUCCESS);
}

void print_params(char **arg)
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
	else if (ft_strncmp(params[0], "co", 3) == 0)
		error = set_env(params, &env->shape, T_CONE, F_COOR | F_ORIEN
				| F_DIA | F_HEI | F_RGB);
	else
		error = BAD_ARGUMENTS;
	printf("============\n\n");
	nta_free((void **)params);
	return (error);
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
	close(fd);
}
