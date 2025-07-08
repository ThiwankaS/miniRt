# include "../../include/miniRt.h"

void tuple_add(t_tuple *t0, t_tuple *t1, t_tuple *t2)
{
	t0->t[0] = t1->t[0] + t2->t[0];
	t0->t[1] = t1->t[1] + t2->t[1];
	t0->t[2] = t1->t[2] + t2->t[2];
	t0->t[3] = t1->t[3] + t2->t[3];
}

void tuple_subtract(t_tuple *t0, t_tuple *t1, t_tuple *t2)
{
	t0->t[0] = t1->t[0] - t2->t[0];
	t0->t[1] = t1->t[1] - t2->t[1];
	t0->t[2] = t1->t[2] - t2->t[2];
	t0->t[3] = t1->t[3] - t2->t[3];
}

void tuple_negate(t_tuple *t1, t_tuple *t2)
{
	t_tuple zero;
	vector(&zero, 0.0, 0.0, 0.0);
	tuple_subtract(t1, &zero, t2);
}

void tuple_multiply_scalor(t_tuple *t0, t_tuple *t1, float a)
{
	t0->t[0] = t1->t[0] * a;
	t0->t[1] = t1->t[1] * a;
	t0->t[2] = t1->t[2] * a;
	t0->t[3] = t1->t[3] * a;
}

void tuple_divide_scalor(t_tuple *t0, t_tuple *t1, float a)
{
	float b;

	if( a == 0.0)
	{
		t0->t[0] = 0.0;
		t0->t[1] = 0.0;
		t0->t[2] = 0.0;
		t0->t[3] = 0.0;
	}
	b = 1 / a;
	tuple_multiply_scalor(t0, t1, b);
}
