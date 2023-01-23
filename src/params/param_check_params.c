/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_check_params.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 14:26:56 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/23 15:31:38 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "params.h"

static int	check_vector(char **params)
{
	if (ft_strarrlen(params) != 3)
		return (nta_free((void **)params), EXIT_FAILURE);
	if (isnum(params[0]) == 0 || isnum(params[1]) == 0 || isnum(params[2]) == 0)
		return (nta_free((void **)params), EXIT_FAILURE);
	return (nta_free((void **)params), EXIT_SUCCESS);
}

static int	check_v3(char **params)
{
	if (ft_strarrlen(params) != 3)
		return (nta_free((void **)params), EXIT_FAILURE);
	if (isnum(params[0]) == 0 || isnum(params[1]) == 0 || isnum(params[2]) == 0)
		return (nta_free((void **)params), EXIT_FAILURE);
	return (nta_free((void **)params), EXIT_SUCCESS);
}

static int	check_shape(char **params, int flag)
{
	int	i;

	i = 0;
	printf("checking parameters for %s\n", params[0]);
	if (ft_strarrlen(params) != count_bits(flag) + 1
		&& ft_strarrlen(params) != count_bits(flag))
		return (EXIT_FAILURE);
	if ((flag & F_COOR) == F_COOR && check_v3(ft_split(params[++i], ',')))
		return (EXIT_FAILURE);
	if ((flag & F_ORIEN) == F_ORIEN
		&& check_vector(ft_split(params[++i], ',')))
		return (EXIT_FAILURE);
	if ((flag & F_DIA) == F_DIA && ft_atod(params[++i]) <= 0)
		return (EXIT_FAILURE);
	if ((flag & F_HEI) == F_HEI && ft_atod(params[++i]) <= 0)
		return (EXIT_FAILURE);
	if ((flag & F_RGB) == F_RGB && check_v3(ft_split(params[++i], ',')))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/// @brief check the give parameters
/// @param params (splited line)
/// @param type (See minirt_define.h)
/// @param flag (See minirt_define.h)
/// @return exit code
int	check_params(char **params, int type, int flag)
{
	if (type == T_AMB)
	{
		if (ft_strarrlen(params) != 3 || ft_atod(params[1]) < 0
			|| ft_atod(params[1]) > 1 || check_v3(ft_split(params[2], ',')))
			return (EXIT_FAILURE);
	}
	else if (type == T_CAM)
	{
		if (ft_strarrlen(params) != 4 || check_v3(ft_split(params[1], ','))
			|| check_vector(ft_split(params[2], ','))
			|| ft_atod(params[3]) < 0.1f || ft_atod(params[3]) > 179.9f)
			return (EXIT_FAILURE);
	}
	else if (type == T_LIGHT)
	{
		if (ft_strarrlen(params) != 4 || check_v3(ft_split(params[1], ','))
			|| ft_atod(params[2]) < 0 || ft_atod(params[2]) > 1
			|| check_v3(ft_split(params[3], ',')))
			return (EXIT_FAILURE);
	}
	else if (type > T_SHAPE)
		if (check_shape(params, flag))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
