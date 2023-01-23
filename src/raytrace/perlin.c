/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <abossel@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:59:29 by abossel           #+#    #+#             */
/*   Updated: 2023/01/13 20:51:36 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

typedef struct s_perlin
{
	int		x;
	int		y;
	int		z;
	int		a;
	int		b;
	int		aa;
	int		ab;
	int		ba;
	int		bb;
	float	u;
	float	v;
	float	w;
}	t_perlin;

int	perm(int i)
{
	char	c;

	c = ("\x97\xa0\x89\x5b\x5a\x0f\x83\x0d\xc9\x5f\x60\x35\xc2\xe9\x07"
			"\xe1\x8c\x24\x67\x1e\x45\x8e\x08\x63\x25\xf0\x15\x0a\x17\xbe"
			"\x06\x94\xf7\x78\xea\x4b\x00\x1a\xc5\x3e\x5e\xfc\xdb\xcb\x75"
			"\x23\x0b\x20\x39\xb1\x21\x58\xed\x95\x38\x57\xae\x14\x7d\x88"
			"\xab\xa8\x44\xaf\x4a\xa5\x47\x86\x8b\x30\x1b\xa6\x4d\x92\x9e"
			"\xe7\x53\x6f\xe5\x7a\x3c\xd3\x85\xe6\xdc\x69\x5c\x29\x37\x2e"
			"\xf5\x28\xf4\x66\x8f\x36\x41\x19\x3f\xa1\x01\xd8\x50\x49\xd1"
			"\x4c\x84\xbb\xd0\x59\x12\xa9\xc8\xc4\x87\x82\x74\xbc\x9f\x56"
			"\xa4\x64\x6d\xc6\xad\xba\x03\x40\x34\xd9\xe2\xfa\x7c\x7b\x05"
			"\xca\x26\x93\x76\x7e\xff\x52\x55\xd4\xcf\xce\x3b\xe3\x2f\x10"
			"\x3a\x11\xb6\xbd\x1c\x2a\xdf\xb7\xaa\xd5\x77\xf8\x98\x02\x2c"
			"\x9a\xa3\x46\xdd\x99\x65\x9b\xa7\x2b\xac\x09\x81\x16\x27\xfd"
			"\x13\x62\x6c\x6e\x4f\x71\xe0\xe8\xb2\xb9\x70\x68\xda\xf6\x61"
			"\xe4\xfb\x22\xf2\xc1\xee\xd2\x90\x0c\xbf\xb3\xa2\xf1\x51\x33"
			"\x91\xeb\xf9\x0e\xef\x6b\x31\xc0\xd6\x1f\xb5\xc7\x6a\x9d\xb8"
			"\x54\xcc\xb0\x73\x79\x32\x2d\x7f\x04\x96\xfe\x8a\xec\xcd\x5d"
			"\xde\x72\x43\x1d\x18\x48\xf3\x8d\x80\xc3\x4e\x42\xd7\x3d\x9c"
			"\xb4")[i & 255];
	return ((int)((unsigned char)c));
}

float	fade(float t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

float	lerp(float t, float a, float b)
{
	return (a + t * (b - a));
}

float	grad(int hash, float x, float y, float z)
{
	int		h;
	float	u;
	float	v;
	float	g;

	h = hash & 15;
	if (h < 8)
		u = x;
	else
		u = y;
	if (h < 4)
		v = y;
	else if (h == 12 || h == 14)
		v = x;
	else
		v = z;
	if ((h & 1) == 0)
		g = u;
	else
		g = -u;
	if ((h & 2) == 0)
		g += v;
	else
		g -= v;
	return (g);
}

float	noise(float x, float y, float z)
{
	t_perlin	p;

	p.x = (int)floor(x) & 255;
	p.y = (int)floor(y) & 255;
	p.z = (int)floor(z) & 255;
	x -= floor(x);
	y -= floor(y);
	z -= floor(z);
	p.a = perm(p.x) + p.y;
	p.b = perm(p.x + 1) + p.y;
	p.u = fade(x);
	p.v = fade(y);
	p.w = fade(z);
	p.aa = perm(p.a) + p.z;
	p.ab = perm(p.a + 1) + p.z;
	p.ba = perm(p.b) + p.z;
	p.bb = perm(p.b + 1) + p.z;
	return (lerp(p.w, lerp(p.v, lerp(p.u, grad(perm(p.aa), x, y, z),
					grad(perm(p.ba), x - 1, y, z)),
				lerp(p.u, grad(perm(p.ab), x, y - 1, z),
					grad(perm(p.bb), x - 1, y - 1, z))),
			lerp(p.v, lerp(p.u, grad(perm(p.aa + 1), x, y, z - 1),
					grad(perm(p.ba + 1), x - 1, y, z - 1)),
				lerp(p.u, grad(perm(p.ab + 1), x, y - 1, z - 1),
					grad(perm(p.bb + 1), x - 1, y - 1, z - 1)))));
}
