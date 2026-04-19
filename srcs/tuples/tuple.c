#include "../../include/miniRt.h"

void	point(t_tuple *p, float x, float y, float z)
{
	p->t[0] = x;
	p->t[1] = y;
	p->t[2] = z;
	p->t[3] = 1.0;
}

void	color(t_tuple *p, float x, float y, float z)
{
	p->t[0] = x;
	p->t[1] = y;
	p->t[2] = z;
	p->t[3] = 1.0;
}

void	vector(t_tuple *p, float x, float y, float z)
{
	p->t[0] = x;
	p->t[1] = y;
	p->t[2] = z;
	p->t[3] = 0.0;
}

void	tuple_print(t_tuple *tp)
{
	printf(" | x : %6.3f", tp->t[0]);
	printf(" | y : %6.3f", tp->t[1]);
	printf(" | z : %6.3f", tp->t[2]);
	printf(" | w : %6.3f\n", tp->t[3]);
}

t_tuple	tuple_add(t_tuple *t1, t_tuple *t2)
{
	t_tuple	result;

	result.t[0] = t1->t[0] + t2->t[0];
	result.t[1] = t1->t[1] + t2->t[1];
	result.t[2] = t1->t[2] + t2->t[2];
	result.t[3] = t1->t[3] + t2->t[3];
	return (result);
}

t_tuple	tuple_subtract(t_tuple *t1, t_tuple *t2)
{
	t_tuple	result;

	result.t[0] = t1->t[0] - t2->t[0];
	result.t[1] = t1->t[1] - t2->t[1];
	result.t[2] = t1->t[2] - t2->t[2];
	result.t[3] = t1->t[3] - t2->t[3];
	return (result);
}

t_tuple	tuple_negate(t_tuple *t2)
{
	t_tuple	zero;

	vector(&zero, 0.0, 0.0, 0.0);
	return (tuple_subtract(&zero, t2));
}

t_tuple	tuple_multiply_scalar(t_tuple *t1, float a)
{
	t_tuple	result;

	result.t[0] = t1->t[0] * a;
	result.t[1] = t1->t[1] * a;
	result.t[2] = t1->t[2] * a;
	result.t[3] = t1->t[3] * a;
	return (result);
}

t_tuple	tuple_divide_scalar(t_tuple *t1, float a)
{
	if (a == 0.0f)
		return ((t_tuple){{0.0, 0.0, 0.0, 0.0}});
	return (tuple_multiply_scalar(t1, 1.0f / a));
}

float	tuple_magnitude(t_tuple *t0)
{
	float	x_sq;
	float	y_sq;
	float	z_sq;
	float	w_sq;

	x_sq = t0->t[0] * t0->t[0];
	y_sq = t0->t[1] * t0->t[1];
	z_sq = t0->t[2] * t0->t[2];
	w_sq = t0->t[3] * t0->t[3];
	return (sqrtf(x_sq + y_sq + z_sq + w_sq));
}

float	dot(t_tuple *t1, t_tuple *t2)
{
	float	sum;

	sum = 0.0f;
	sum += t1->t[0] * t2->t[0];
	sum += t1->t[1] * t2->t[1];
	sum += t1->t[2] * t2->t[2];
	sum += t1->t[3] * t2->t[3];
	return (sum);
}

t_tuple	normalize(t_tuple *t1)
{
	float	mag;

	mag = tuple_magnitude(t1);
	return (tuple_divide_scalar(t1, mag));
}

t_tuple	cross(t_tuple *t1, t_tuple *t2)
{
	t_tuple	result;

	result.t[0] = t1->t[1] * t2->t[2] - t1->t[2] * t2->t[1];
	result.t[1] = t1->t[2] * t2->t[0] - t1->t[0] * t2->t[2];
	result.t[2] = t1->t[0] * t2->t[1] - t1->t[1] * t2->t[0];
	result.t[3] = 0.0;
	return (result);
}

t_tuple	schur_product(t_tuple *t1, t_tuple *t2)
{
	t_tuple	result;

	result.t[0] = t1->t[0] * t2->t[0];
	result.t[1] = t1->t[1] * t2->t[1];
	result.t[2] = t1->t[2] * t2->t[2];
	result.t[3] = t1->t[3] * t2->t[3];
	return (result);
}
