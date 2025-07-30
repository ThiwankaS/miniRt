/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 02:26:59 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/29 23:01:20 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Calculates the position along a ray at distance `t` from the origin.
 * Stores the resulting point in `pp`.
 */
void	position(t_tuple *pp, t_ray *r, float t)
{
	pp->t[0] = r->origin.t[0] + r->direction.t[0] * t;
	pp->t[1] = r->origin.t[1] + r->direction.t[1] * t;
	pp->t[2] = r->origin.t[2] + r->direction.t[2] * t;
	pp->t[3] = 1.0f;
}

t_hit	find_hit(t_world *world, t_ray *ray)
{
	t_hit		closest;
	t_object	*object;
	t_ray		local_ray;

	closest.t = INFINITY;
	closest.hit = false;
	closest.object = NULL;
	object = world->components;
	while (object)
	{
		local_ray = transform(ray, &object->invs);
		if (object->type == SPHERE)
			find_hit_sphere(object, &local_ray, &closest);
		else if (object->type == PLANE)
			find_hit_plane(object, &local_ray, &closest);
		else if (object->type == CYLINDER)
			find_hit_cylinder(object, &local_ray, &closest);
		object = object->next;
	}
	return (closest);
}
