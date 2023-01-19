/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 10:04:06 by abossel           #+#    #+#             */
/*   Updated: 2023/01/19 11:13:38 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "raytrace.h"

int	is_mat(t_obj *shape, char *name)
{
	if (ft_strncmp(shape->material, name, ft_strlen(name) + 1) == 0)
		return (1);
	return (0);
}

t_mat	get_mat_glass(void)
{
	t_mat	m;

	m.specular = 1.5f;
	m.diffuse = 0.7f;
	m.ambient = 0.5f;
	m.shine = 125.0f;
	return (m);
}

t_mat	get_mat_paper(void)
{
	t_mat	m;

	m.specular = 0.0f;
	m.diffuse = 0.7f;
	m.ambient = 0.5f;
	m.shine = 0.0f;
	return (m);
}

t_mat	get_material(char *name)
{
	if (ft_strncmp("glass", name, 6) == 0)
		return (get_mat_glass());
	if (ft_strncmp("paper", name, 6) == 0)
		return (get_mat_paper());
	if (ft_strncmp("checkerboard", name, 13) == 0)
		return (get_mat_paper());
	if (ft_strncmp("bumpy", name, 13) == 0)
		return (get_mat_glass());
	return (get_mat_glass());
}
