/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 02:26:59 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/13 09:17:19 by tsomacha         ###   ########.fr       */
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

t_hit	find_hit(t_world *world, t_ray *ray)
{
	t_object	*object;
	t_hit		closest;
	t_ray		local_ray;
	float		t;

	closest.hit = false;
	closest.t = INFINITY;
	closest.object = NULL;

	object = world->components;
	while (object)
	{
		transform(&local_ray, ray, &object->invs);
		if (object->type == SPHERE)
		{
			t_tuple sphere_to_ray;
			t_tuple origin;
			float a, b, c, discriminant;

			point(&origin, 0, 0, 0);
			tuple_subtract(&sphere_to_ray, &local_ray.origin, &origin);
			a = dot(&local_ray.direction, &local_ray.direction);
			b = 2 * dot(&local_ray.direction, &sphere_to_ray);
			c = dot(&sphere_to_ray, &sphere_to_ray) - 1;
			discriminant = b * b - 4 * a * c;

			if (discriminant >= 0.0f)
			{
				float sqrt_d = sqrtf(discriminant);
				float t1 = (-b - sqrt_d) / (2 * a);
				float t2 = (-b + sqrt_d) / (2 * a);

				if (t1 > 0.0f && t1 < closest.t)
				{
					closest.t = t1;
					closest.object = object;
					closest.hit = true;
				}
				if (t2 > 0.0f && t2 < closest.t)
				{
					closest.t = t2;
					closest.object = object;
					closest.hit = true;
				}
			}
		}
		else if (object->type == PLANE)
		{
			if (fabs(local_ray.direction.t[1]) >= 1e-6)
			{
				t = -local_ray.origin.t[1] / local_ray.direction.t[1];
				if (t > 0.0f && t < closest.t)
				{
					closest.t = t;
					closest.object = object;
					closest.hit = true;
				}
			}
		}
		object = object->next;
	}
	return (closest);
}
