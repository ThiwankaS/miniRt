#include "../../include/miniRt.h"

void position(t_tuple *pp, t_ray *r, float t)
{
	t_tuple temp;

	tuple_multiply_scalor(&temp, r->direction, t);
	tuple_add(pp, r->origin, &temp);
}
t_intersect *intersection(double t, t_object *object)
{
	t_intersect *i = calloc(1, sizeof(t_intersect));
	if(!i)
		return NULL;
	i->value = t;
	i->object = object;
	return i;
}

t_intersect *calculate_intersects(t_object *object, t_ray *rp)
{
	t_mat	inverse;
	t_ray	r;
	t_tuple	center;
	t_tuple	distance;
	t_intersect *intersects;

	matrix_inverse(&inverse, object->transform);
	transform(&r, rp, inverse);
	point(&center, object->x, object->y, object->z);
	substrctTuples(&distance, r.origin, center);
	float a = dot(r.direction, r.direction);
	float b = 2.0 * dot(r.direction, &distance);
	float c = dot(&distance, &distance) - 1;
	float discriminent = (b * b) - (4 * a * c);
	if (discriminent < 0)
		return (NULL);
	intersects = ft_calloc(2, sizeof(t_intersect));
	if (!intersects)
		return (NULL);
	intersects[0].value = (-b - sqrt(discriminent)) / (2 * a);
	intersects[0].object = object;
	intersects[1].value = (-b + sqrt(discriminent)) / (2 * a);
	intersects[1].object = object;
	return (intersects);
}

t_intersections *intersections(t_intersections *xs, t_intersect *intersect)
{
	if(!xs)
	{
		t_intersections *xs = calloc(1, sizeof(t_intersections));
		if(!xs)
			return NULL;
		xs->intersect = intersect;
		xs->next = NULL;
		xs->count = 1;
		return xs;
	}
	t_intersections *current = xs, *previous;
	while(current)
	{
		previous = current;
		current = current->next;
	}
	t_intersections *new = calloc(1, sizeof(t_intersections));
	if(!new)
		return xs;
	new->intersect = intersect;
	new->next = NULL;
	previous->next = new;
	xs->count++;
	return xs;
}

t_intersect *hit(t_intersections *xs)
{
	t_intersect *i = NULL;
	t_intersections *current = xs, *previous;
	while(current)
	{
		previous = current;
		if(previous->intersect->value > 0.0)
		{
			if(!i || previous->intersect->value < i->value)
				i = previous->intersect;
		}
		current = current->next;
	}
	return i;
}
