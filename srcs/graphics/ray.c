#include "../../include/miniRt.h"

void position(t_tuple *pp, t_ray *r, float t)
{
	t_tuple temp;

	tuple_multiply_scalor(&temp, &r->direction, t);
	tuple_add(pp, &r->origin, &temp);
}
t_intersect *intersection(double t, t_object *object)
{
	t_intersect *i = ft_calloc(1, sizeof(t_intersect));
	if(!i)
		return NULL;
	i->value = t;
	i->object = object;
	return i;
}

t_intersect *calculate_intersects(t_object *object, t_ray *rp)
{
	t_tuple		abs;
	t_tuple		sphere_to_ray;
	t_intersect	*intersects;
	t_mat		invs;
	t_ray		r;
	float		a;
	float		b;
	float		c;
	float		discriminent;

	point(&abs, 0, 0, 0);
	matrix_inverse(&invs, &object->transform);
	transform(&r, rp, &invs);
	tuple_subtract(&sphere_to_ray, &r.origin, &abs);
	a = dot(&r.direction, &r.direction);
	b = 2 * dot(&r.direction, &sphere_to_ray);
	c = dot(&sphere_to_ray, &sphere_to_ray) - 1;
	discriminent = (b * b) - (4 * a * c);
	if (discriminent < 0)
		return NULL;
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
		t_intersections *xs = ft_calloc(1, sizeof(t_intersections));
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
	t_intersections *new = ft_calloc(1, sizeof(t_intersections));
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
