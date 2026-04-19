#include "../../include/miniRt.h"

static void	try_closest_body_hit(t_object *object, t_hit *h,
		float t1, float t2, float y1, float y2, float y_min, float y_max)
{
	float	min_t;

	min_t = INFINITY;
	if (t1 > EPSILON && y1 >= y_min && y1 <= y_max)
		min_t = t1;
	if (t2 > EPSILON && y2 >= y_min && y2 <= y_max && t2 < min_t)
		min_t = t2;
	if (min_t < h->t)
	{
		h->t = min_t;
		h->object = object;
		h->hit = true;
	}
}

void	find_hit_cylinder(t_object *object, t_ray *r, t_hit *h)
{
	float	dx;
	float	dy;
	float	dz;
	float	ox;
	float	oy;
	float	oz;
	float	y_min;
	float	y_max;
	float	radius_sq;
	float	a;
	float	b;
	float	c;
	float	disc;
	float	sqrt_disc;
	float	t1;
	float	t2;
	float	y_at_t1;
	float	y_at_t2;

	dx = r->direction.t[0];
	dy = r->direction.t[1];
	dz = r->direction.t[2];
	ox = r->origin.t[0];
	oy = r->origin.t[1];
	oz = r->origin.t[2];
	y_min = -object->height / 2.0f;
	y_max = object->height / 2.0f;
	radius_sq = object->radius * object->radius;
	a = dx * dx + dz * dz;
	if (fabsf(a) < EPSILON)
	{
		hit_cap(object, r, h);
		return ;
	}
	b = 2.0f * ox * dx + 2.0f * oz * dz;
	c = ox * ox + oz * oz - radius_sq;
	disc = b * b - 4 * a * c;
	if (disc < 0)
	{
		hit_cap(object, r, h);
		return ;
	}
	sqrt_disc = sqrtf(disc);
	t1 = (-b - sqrt_disc) / (2.0f * a);
	t2 = (-b + sqrt_disc) / (2.0f * a);
	y_at_t1 = oy + t1 * dy;
	y_at_t2 = oy + t2 * dy;
	try_closest_body_hit(object, h, t1, t2, y_at_t1, y_at_t2, y_min, y_max);
	hit_cap(object, r, h);
}

static void	try_cap_at_y(t_object *object, t_hit *h, float dx, float dz,
		float ox, float oz, float radius_sq, float t)
{
	float	x;
	float	z;
	float	dist_sq;

	x = ox + dx * t;
	z = oz + dz * t;
	dist_sq = x * x + z * z;
	if (dist_sq <= radius_sq)
	{
		h->t = t;
		h->object = object;
		h->hit = true;
	}
}

void	hit_cap(t_object *object, t_ray *r, t_hit *h)
{
	float	dx;
	float	dy;
	float	dz;
	float	ox;
	float	oy;
	float	oz;
	float	y_min;
	float	y_max;
	float	radius_sq;
	float	t;

	dx = r->direction.t[0];
	dy = r->direction.t[1];
	dz = r->direction.t[2];
	ox = r->origin.t[0];
	oy = r->origin.t[1];
	oz = r->origin.t[2];
	y_min = -object->height / 2.0f;
	y_max = object->height / 2.0f;
	radius_sq = object->radius * object->radius;
	if (fabsf(dy) <= EPSILON)
		return ;
	t = (y_min - oy) / dy;
	if (t > EPSILON && t < h->t)
		try_cap_at_y(object, h, dx, dz, ox, oz, radius_sq, t);
	t = (y_max - oy) / dy;
	if (t > EPSILON && t < h->t)
		try_cap_at_y(object, h, dx, dz, ox, oz, radius_sq, t);
}
