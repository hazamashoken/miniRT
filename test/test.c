#include "vector.h"

int	main(void)
{
	t_v4si a, b, c;
	long l;

	a[0] = 2;
	a[1] = 3;
	b[0] = 3;
	b[1] = 2;
	c[0] = 2;
	c[1] = 2;
	a = b * c;    /* a = b + {1,1,1,1}; */
	// a = 2 * b;    /* a = {2,2,2,2} * b; */
	// a = normalize(a);
	printf("%f %f %f %f\n",a[0],a[1],a[2],a[3]);
}
