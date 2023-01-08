#ifndef RAYTRACE_H
# define RAYTRACE_H

#include "vector3.h"
#include "mlx_render.h"
#include "minirt.h"

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
}	t_hit;

typedef struct s_mat
{
	float	specular;
	float	diffuse;
	float	ambient;
	float	shine;
}	t_mat;

void	raytrace(t_app *app, t_env *env);
int		sphere_hit_quick(t_ray *r, t_hit *h, t_v3 s_centre, float s_radius);
int		sphere_hit(t_ray *r, t_hit *h, t_v3 s_centre, float s_radius);

t_hit	shape_hit(t_ray *r, t_shape *s);
float	shape_hit_quick(t_ray *r, t_shape *s);
t_shape	*find_shape(t_env *env, t_ray *r);

float	phong_lighting(t_ray *r, t_hit *h, t_mat *m, t_v3 light_dir);
float	diffuse_lighting(t_ray *r, t_hit *h, t_mat *m, t_v3 light_dir);
int		light_hit(t_env *env, t_v3 point, t_light *l);

#endif
