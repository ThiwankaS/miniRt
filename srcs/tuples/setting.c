# include "../../include/miniRt.h"

void point(t_tuple *p, float x, float y, float z)
{
	p->t[0] = x;
	p->t[1] = y;
	p->t[2] = z;
	p->t[3] = 1.0;
}

void color(t_tuple *p, float x, float y, float z)
{
	p->t[0] = x;
	p->t[1] = y;
	p->t[2] = z;
	p->t[3] = 1.0;
}

void vector(t_tuple *p, float x, float y, float z)
{
	p->t[0] = x;
	p->t[1] = y;
	p->t[2] = z;
	p->t[3] = 0.0;
}

void tuple_print(t_tuple *tp)
{
	printf("x : %.2f\t", tp->t[0]);
	printf("y : %.2f\t", tp->t[1]);
	printf("z : %.2f\t", tp->t[2]);
	printf("w : %.2f\n", tp->t[3]);
}
