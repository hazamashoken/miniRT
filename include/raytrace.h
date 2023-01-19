/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 23:28:49 by tliangso          #+#    #+#             */
/*   Updated: 2023/01/15 10:27:45 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "vector3.h"
# include "mlx_render.h"
# include "minirt.h"

typedef struct s_ray
{
	t_v3	origin;
	t_v3	direction;
}	t_ray;

/*
 * distance: distance to near intersection
 * point: near intersection point
 * normal: normal vector of near intersection point
 * reflect: reflection vector of the camera to point vector
 */
typedef struct s_hit
{
	float	distance;
	t_v3	point;
	t_v3	normal;
	t_v3	reflect;
	float	u;
	float	v;
}	t_hit;

typedef struct s_mat
{
	float	specular;
	float	diffuse;
	float	ambient;
	float	shine;
}	t_mat;

void	raytrace(t_app *app, t_env *env);

int		sphere_hit_quick(t_ray *r, t_hit *h, t_obj *s);
int		sphere_hit(t_ray *r, t_hit *h, t_obj *s);

int		plane_hit_quick(t_ray *r, t_hit *h, t_v3 p_centre, t_v3 p_normal);
int		plane_hit(t_ray *r, t_hit *h, t_v3 p_centre, t_v3 p_normal);

int		disk_hit(t_ray *r, t_hit *h, t_v3 d_centre, t_v3 d_normal, float d_radius);
int		tube_hit_quick(t_ray *r, t_hit *h, t_v3 t_centre, t_v3 t_direction, float t_radius);
int		tube_hit(t_ray *r, t_hit *h, t_v3 t_centre, t_v3 t_direction, float t_radius);
int		cylinder_hit(t_ray *r, t_hit *h, t_v3 c_centre, t_v3 c_direction, float c_radius, float c_height);
int		cone_hit(t_ray *r, t_hit *h, t_v3 c_centre, t_v3 c_direction, float c_radius, float c_height);
int		cone_quick_hit(t_ray *r, t_hit *h, t_v3 t_centre, t_v3 t_direction, float t_radius, float height);

t_hit	shape_hit(t_ray *r, t_obj *s);
float	shape_hit_quick(t_ray *r, t_obj *s);
t_obj	*find_shape(t_env *env, t_ray *r);

float	phong_lighting(t_ray *r, t_hit *h, t_mat *m, t_v3 light_dir);
float	diffuse_lighting(t_hit *h, t_mat *m, t_v3 light_dir);
int		light_hit(t_env *env, t_v3 point, t_obj *l);
t_v3	reflect_colour(t_v3 colour, t_v3 light);
float	flat_lighting(t_hit *h, t_mat *m, t_v3 light_dir);

t_mat	get_material(char *name);
int		is_mat(t_obj *shape, char *name);

int		checkerboard_black(t_hit *h, float scale);
t_v3	bumpmap_normal(t_hit *h);

float	noise(float x, float y, float z);
float	noise2(float x, float y);

#endif
