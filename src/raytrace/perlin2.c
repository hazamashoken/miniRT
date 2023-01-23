/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abossel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 11:04:24 by abossel           #+#    #+#             */
/*   Updated: 2023/01/19 11:04:27 by abossel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

typedef struct s_perlin2
{
	int		ix0;
	int		iy0;
	int		ix1;
	int		iy1;
	float	fx0;
	float	fy0;
	float	fx1;
	float	fy1;
	float	t;
	float	s;
}	t_perlin2;

static int	perm2(int i)
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
			"\xb4")[i & 0xff];
	return ((int)((unsigned char)c));
}

static float	fade2(float t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

static float	lerp2(float t, float a, float b)
{
	return (a + t * (b - a));
}

static float	grad2(int hash, float x, float y)
{
	int		h;
	float	u;
	float	v;
	float	g;

	h = hash & 7;
	if (h < 4)
		u = x;
	else
		u = y;
	if (h < 4)
		v = y;
	else
		v = x;
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

float	noise2(float x, float y)
{
	t_perlin2	p;

	p.ix0 = floor(x);
	p.iy0 = floor(y);
	p.fx0 = x - p.ix0;
	p.fy0 = y - p.iy0;
	p.fx1 = p.fx0 - 1.0;
	p.fy1 = p.fy0 - 1.0;
	p.ix1 = (p.ix0 + 1) & 0xff;
	p.iy1 = (p.iy0 + 1) & 0xff;
	p.ix0 = p.ix0 & 0xff;
	p.iy0 = p.iy0 & 0xff;
	p.t = fade2(p.fy0);
	p.s = fade2(p.fx0);
	return (lerp2(p.s,
			lerp2(p.t,
				grad2(perm2(p.ix0 + perm2(p.iy0)), p.fx0, p.fy0),
				grad2(perm2(p.ix0 + perm2(p.iy1)), p.fx0, p.fy1)),
			lerp2(p.t,
				grad2(perm2(p.ix1 + perm2(p.iy0)), p.fx1, p.fy0),
				grad2(perm2(p.ix1 + perm2(p.iy1)), p.fx1, p.fy1))));
}
