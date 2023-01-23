/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliangso <earth78203@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:14:53 by abossel           #+#    #+#             */
/*   Updated: 2023/01/13 12:38:08 by tliangso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "raytrace.h"

/*
 * calculate phong lighting for a single light source
 * returns the light intensity between 0 and 1
 * I = Kd * (N dot L) + Ks * (R dot V) ^ Ka
 * N = surface normal
 * L = unit vector from intersection point and light
 * V = unit vector from intersection point and camera
 * R = light reflection unit vector
 * Kd = diffuse reflectivity
 * Ks = specular reflectivity
 * Ka = shinyness
 */
float	phong_lighting(t_ray *r, t_hit *h, t_mat *m, t_v3 light_dir)
{
	t_v3	camera_dir;
	t_v3	reflect_dir;
	float	intensity;

	camera_dir = v3norm(v3sub(r->origin, h->point));
	reflect_dir = v3norm(v3reflect(light_dir, h->normal));
	intensity = m->diffuse * v3dot(v3neg(light_dir), h->normal)
		+ m->specular * pow(v3dot(reflect_dir, camera_dir), m->shine);
	intensity = clamp(intensity, 0.0f, 1.0f);
	return (intensity);
}

/*
 * calculate diffuse lighting for a single light source
 * returns the light intensity between 0 and 1
 * I = Kd * (N dot L)
 * N = surface normal
 * L = unit vector from intersection point and light
 * Kd = diffuse reflectivity
 */
float	diffuse_lighting(t_hit *h, t_mat *m, t_v3 light_dir)
{
	float	intensity;

	intensity = m->diffuse * v3dot(v3neg(light_dir), h->normal);
	intensity = clamp(intensity, 0.0f, 1.0f);
	return (intensity);
}

/*
 * check if a light hits a point
 */
int	light_hit(t_env *env, t_v3 point, t_obj *l)
{
	t_ray	light_ray;
	float	light_dist;
	t_obj	*shape;

	light_ray.origin = point;
	light_ray.direction = v3norm(v3sub(l->coordinate, point));
	light_dist = v3mag(v3sub(l->coordinate, point));
	shape = find_shape(env, &light_ray);
	if (shape == NULL || shape_hit_quick(&light_ray, shape) > light_dist)
		return (1);
	return (0);
}

/*
 * reflects the light based on the colour of an object
 * returns the reflected light colour
 * e.g. a green object shouldn't reflect red light
 * colour is the colour of the object
 * light is the colour of the light
 */
t_v3	reflect_colour(t_v3 colour, t_v3 light)
{
	t_v3	reflect;

	reflect = v3scale(colour, 1.0f / 255.0f);
	reflect.r *= light.r;
	reflect.g *= light.g;
	reflect.b *= light.b;
	return (reflect);
}

float	flat_lighting(t_hit *h, t_mat *m, t_v3 light_dir)
{
	(void)h;
	(void)m;
	(void)light_dir;
	return (1.0f);
}
