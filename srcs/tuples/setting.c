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
