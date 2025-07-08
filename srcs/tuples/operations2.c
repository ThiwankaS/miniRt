# include "../../include/miniRt.h"

float tuple_magnitute(t_tuple *t0)
{
	float x_squared;
	float y_squared;
	float z_squared;
	float w_squared;
	float squared;

	x_squared = t0->t[0] * t0->t[0];
	y_squared = t0->t[1] * t0->t[1];
	z_squared = t0->t[2] * t0->t[2];
	w_squared = t0->t[3] * t0->t[3];
	squared = x_squared + y_squared + z_squared + w_squared;
	return (sqrtf(squared));
}

float dot(t_tuple *t1, t_tuple *t2)
{
	float sum;

	sum = 0.0;
	sum += t1->t[0] * t2->t[0];
	sum += t1->t[1] * t2->t[1];
	sum += t1->t[2] * t2->t[2];
	sum += t1->t[3] * t2->t[3];
	return sum;
}

void normalize(t_tuple *t0, t_tuple *t1)
{
	float mag;
	mag = tuple_magnitute(t1);
	tuple_divide_scalor(t0, t1, mag);
}

void cross(t_tuple *t0, t_tuple *t1, t_tuple *t2)
{
	t0->t[0] = t1->t[1] * t2->t[2] - t1->t[2] * t2->t[1];
	t0->t[1] = t1->t[2] * t2->t[0] - t1->t[0] * t2->t[2];
	t0->t[2] = t1->t[0] * t2->t[1] - t1->t[1] * t2->t[0];
	t0->t[3] = 0.0;
}

void schur_product(t_tuple *t0, t_tuple *t1, t_tuple *t2)
{
	t0->t[0] = t1->t[0] * t2->t[0];
	t0->t[1] = t1->t[1] * t2->t[1];
	t0->t[2] = t1->t[2] * t2->t[2];
	t0->t[3] = t1->t[3] * t2->t[3];
}
