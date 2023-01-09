/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:11:10 by abossel           #+#    #+#             */
/*   Updated: 2023/01/09 21:23:49 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "raytrace.h"
#include <float.h>

/*
 * get shape intersection information
 * the information is returned in a t_hit
 */
t_hit	shape_hit(t_ray *r, t_shape *s)
{
	t_hit	h;

	h.distance = -1.0f;
	if (s->type == T_SPHERE)
		sphere_hit(r, &h, v4tov3(s->coordinate), s->diameter / 2.0);
	else if (s->type == T_PLANE)
		plane_hit(r, &h, v4tov3(s->coordinate), v4tov3(s->orientation));
	else if (s->type == T_CYLINDER)
		cylinder_hit(r, &h, v4tov3(s->coordinate), v4tov3(s->orientation), s->diameter / 2.0, s->height);
	return (h);
}

/*
 * check if a ray hits a shape
 * returns a float >= 0 if ray r hits shape s
 */
float	shape_hit_quick(t_ray *r, t_shape *s)
{
	t_hit	h;

	h.distance = -1.0f;
	if (s->type == T_SPHERE
		&& sphere_hit_quick(r, &h, v4tov3(s->coordinate), s->diameter / 2.0))
		return (h.distance);
	if (s->type == T_PLANE
		&& plane_hit_quick(r, &h, v4tov3(s->coordinate), v4tov3(s->orientation)))
		return (h.distance);
	if (s->type == T_CYLINDER
		&& cylinder_hit(r, &h, v4tov3(s->coordinate), v4tov3(s->orientation), s->diameter / 2.0, s->height))
		return (h.distance);
	return (-1.0f);
}

/*
 * find the shape closest to the ray
 * returns a pointer to the closest shape from the ray r
 * returns NULL if no shape found
 */
t_shape	*find_shape(t_env *env, t_ray *r)
{
	float	min_dist;
	float	tmp_dist;
	t_shape	*shape;
	int		i;

	i = 0;
	shape = NULL;
	min_dist = FLT_MAX;
	while (env->shape[i] != NULL)
	{
		tmp_dist = shape_hit_quick(r, env->shape[i]);
		if (tmp_dist >= 0.0f && tmp_dist < min_dist)
		{
			min_dist = tmp_dist;
			shape = env->shape[i];
		}
		i++;
	}
	return (shape);
}