#ifndef RAYTRACE_H
# define RAYTRACE_H

#include "vector3.h"

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

t_hit	sphere_hit(t_ray r, t_v3 s_centre, float s_radius);

#endif
