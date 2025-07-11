/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 02:26:59 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/11 06:17:41 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Calculates the position along a ray at distance `t` from the origin.
 * Stores the resulting point in `pp`.
 */
void	position(t_tuple *pp, t_ray *r, float t)
{
	t_tuple	temp;

	tuple_multiply_scalor(&temp, &r->direction, t);
	tuple_add(pp, &r->origin, &temp);
}


t_intersect	*add_node(t_object *object, float t)
{
	t_intersect	*i;

	i = ft_calloc(1, sizeof(t_intersect));
	if (!i)
		return (NULL);
	i->value = t;
	i->object = object;
	i->next = NULL;
	return (i);
}

t_intersect	*cal_intersects(t_object *object, t_ray *rp, t_intersect *xs)
{
	t_tuple	abs;
	t_tuple	sphere_to_ray;
	t_ray	r;
	float	values[4];
	float	discriminent;

	point(&abs, 0, 0, 0);
	transform(&r, rp, &object->invs);
	tuple_subtract(&sphere_to_ray, &r.origin, &abs);
	values[0] = dot(&r.direction, &r.direction);
	values[1] = 2 * dot(&r.direction, &sphere_to_ray);
	values[2] = dot(&sphere_to_ray, &sphere_to_ray) - 1;
	discriminent = (values[1] * values[1]) - (4 * values[0] * values[2]);
	if (discriminent < 0)
		return (NULL);
	values[3] = sqrt(discriminent);
	xs = intersections(xs, object, (-values[1] - values[3]) / (2 * values[0]));
	xs = intersections(xs, object, (-values[1] + values[3]) / (2 * values[0]));
	return (xs);
}


t_intersect	*intersections(t_intersect *xs, t_object *s, float value)
{
	t_intersect	*current;
	t_intersect	*previous;
	t_intersect	*new;

	current = xs;
	previous = NULL;
	while (current)
	{
		previous = current;
		current = current->next;
	}
	new = add_node(s, value);
	if (!new)
		return (NULL);
	if (!xs && !previous)
	{
		new->count = 1;
		return (new);
	}
	previous->next = new;
	xs->count++;
	return (xs);
}


t_intersect	*hit(t_intersect *xs)
{
	t_intersect	*i;
	t_intersect	*current;
	t_intersect	*previous;

	current = xs;
	i = NULL;
	while (current)
	{
		previous = current;
		if (previous->value > 0.0)
		{
			if (!i || previous->value < i->value)
				i = previous;
		}
		current = current->next;
	}
	return (i);
}
