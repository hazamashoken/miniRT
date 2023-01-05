#ifndef RAYTRACE_H
# define RAYTRACE_H

#include "vector3.h"
#include "mlx_render.h"

typedef struct s_ray
{
	t_v3	origin;
	t_v3	direction;
}	t_ray;

typedef struct s_hit
{
	float	distance;
	t_v3	point;
	t_v3	normal;
}	t_hit;

typedef struct s_mat
{
	float	specular;
	float	diffuse;
	float	ambient;
	float	shine;
}	t_mat;

void raytrace(t_app *app, t_v3 origin, t_v3 direction, float fov_degrees);
t_hit	sphere_hit(t_ray r, t_v3 s_centre, float s_radius);

#endif
