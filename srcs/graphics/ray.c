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

/**
 * Initializes a hit record with infinite distance, no hit flag,
 * and the given object.
 * Used as a starting point before performing intersection tests.
 */
void	init_hit_object(t_hit *h, t_object *object)
{
	h->t = INFINITY;
	h->hit = false;
	h->object = object;
}

/**
 * Transforms a ray into an object's local space, normalizes its direction,
 * and tests for intersections based on the object's type. If a closer hit
 * than the current closest is found, updates the closest hit record.
 */
void	process_find_hit(t_object *object, t_ray *ray, t_hit *closest)
{
	t_ray	local_ray;
	t_hit	local_hit;
	float	dir_len;
	float	world_t;

	local_ray = transform(ray, &object->invs);
	dir_len = tuple_magnitute(&local_ray.direction);
	if (dir_len == 0.0f)
		return ;
	local_ray.direction = tuple_divide_scalar(&local_ray.direction, dir_len);
	local_ray.direction.t[3] = 0.0f;
	init_hit_object(&local_hit, object);
	if (object->type == SPHERE)
		find_hit_sphere(object, &local_ray, &local_hit);
	else if (object->type == PLANE)
		find_hit_plane(object, &local_ray, &local_hit);
	else if (object->type == CYLINDER)
		find_hit_cylinder(object, &local_ray, &local_hit);
	world_t = local_hit.t / dir_len;
	if (local_hit.hit && (world_t < closest->t))
	{
		closest->t = world_t;
		closest->hit = true;
		closest->object = object;
	}
}

/**
 * Iterates through all objects in the world and finds the closest intersection
 * point between the given ray and any object. Returns the hit record containing
 * the nearest intersection data, or no-hit if none found.
 */
t_hit	find_hit(t_world *world, t_ray *ray)
{
	t_hit		closest;
	t_object	*object;

	init_hit_object(&closest, NULL);
	object = world->components;
	while (object)
	{
		process_find_hit(object, ray, &closest);
		object = object->next;
	}
	return (closest);
}
