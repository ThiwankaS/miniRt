/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 02:26:59 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/13 09:41:50 by tsomacha         ###   ########.fr       */
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
	t_hit		closest;
	t_object	*object;
	t_ray		local_ray;

	closest.hit = false;
	closest.t = INFINITY;
	closest.object = NULL;

	object = world->components;
	while (object)
	{
		transform(&local_ray, ray, &object->invs);

		if (object->type == SPHERE)
		{
			t_tuple	center, sphere_to_ray;
			float	a, b, c, discriminant, t1, t2;

			point(&center, 0, 0, 0);
			tuple_subtract(&sphere_to_ray, &local_ray.origin, &center);

			a = dot(&local_ray.direction, &local_ray.direction);
			b = 2 * dot(&local_ray.direction, &sphere_to_ray);
			c = dot(&sphere_to_ray, &sphere_to_ray) - 1;
			discriminant = b * b - 4 * a * c;

			if (discriminant >= 0.0f)
			{
				float sqrt_d = sqrtf(discriminant);
				t1 = (-b - sqrt_d) / (2 * a);
				t2 = (-b + sqrt_d) / (2 * a);

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
			if (fabsf(local_ray.direction.t[1]) >= 1e-6f)
			{
				float t = -local_ray.origin.t[1] / local_ray.direction.t[1];
				if (t > 0.0f && t < closest.t)
				{
					closest.t = t;
					closest.object = object;
					closest.hit = true;
				}
			}
		}
		else if (object->type == CYLINDER)
		{
			float a, b, c, discriminant;
			float t1, t2, y1, y2;
			const float min_y = -1.0f; // Replace with object->min if dynamic
			const float max_y =  1.0f; // Replace with object->max if dynamic

			a = local_ray.direction.t[0] * local_ray.direction.t[0] +
				local_ray.direction.t[2] * local_ray.direction.t[2];

			if (fabsf(a) >= 1e-6f)
			{
				b = 2 * (local_ray.origin.t[0] * local_ray.direction.t[0] +
						 local_ray.origin.t[2] * local_ray.direction.t[2]);
				c = local_ray.origin.t[0] * local_ray.origin.t[0] +
					local_ray.origin.t[2] * local_ray.origin.t[2] - 1;
				discriminant = b * b - 4 * a * c;

				if (discriminant >= 0.0f)
				{
					float sqrt_d = sqrtf(discriminant);
					t1 = (-b - sqrt_d) / (2 * a);
					t2 = (-b + sqrt_d) / (2 * a);

					y1 = local_ray.origin.t[1] + t1 * local_ray.direction.t[1];
					y2 = local_ray.origin.t[1] + t2 * local_ray.direction.t[1];

					if (t1 > 0.0f && t1 < closest.t && y1 >= min_y && y1 <= max_y)
					{
						closest.t = t1;
						closest.object = object;
						closest.hit = true;
					}
					if (t2 > 0.0f && t2 < closest.t && y2 >= min_y && y2 <= max_y)
					{
						closest.t = t2;
						closest.object = object;
						closest.hit = true;
					}
				}
			}
		}
		object = object->next;
	}
	return (closest);
}
