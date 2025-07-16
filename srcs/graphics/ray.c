/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 02:26:59 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/16 10:04:56 by tsomacha         ###   ########.fr       */
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
	pp->t[3] = r->origin.t[3] + r->direction.t[3] * t;
}

t_hit find_hit(t_world *world, t_ray *ray)
{
	t_hit closest = { .t = INFINITY, .hit = false, .object = NULL };
	t_object *object = world->components;
	t_ray local_ray;

	while (object)
	{
		transform(&local_ray, ray, &object->invs);
		if (object->type == SPHERE)
		{
			// Sphere assumed centered at (0,0,0)
			float dx = local_ray.origin.t[0];
			float dy = local_ray.origin.t[1];
			float dz = local_ray.origin.t[2];

			float vx = local_ray.direction.t[0];
			float vy = local_ray.direction.t[1];
			float vz = local_ray.direction.t[2];

			float a = vx*vx + vy*vy + vz*vz;
			float b = 2.0f * (vx*dx + vy*dy + vz*dz);
			float c = dx*dx + dy*dy + dz*dz - 1.0f;
			float discriminant = b*b - 4.0f*a*c;

			if (discriminant >= 0.0f)
			{
				float sqrt_d = sqrtf(discriminant);
				float inv2a = 0.5f / a;

				float t1 = (-b - sqrt_d) * inv2a;
				float t2 = (-b + sqrt_d) * inv2a;

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
			float dy = local_ray.direction.t[1];
			if (fabsf(dy) >= 1e-6f)
			{
				float t = -local_ray.origin.t[1] / dy;
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
			const float min_y = -1.0f;
			const float max_y =  1.0f;

			float ox = local_ray.origin.t[0];
			float oz = local_ray.origin.t[2];
			float dx = local_ray.direction.t[0];
			float dz = local_ray.direction.t[2];

			float a = dx*dx + dz*dz;

			if (fabsf(a) >= 1e-6f)
			{
				float b = 2.0f * (ox*dx + oz*dz);
				float c = ox*ox + oz*oz - 1.0f;
				float discriminant = b*b - 4.0f*a*c;

				if (discriminant >= 0.0f)
				{
					float sqrt_d = sqrtf(discriminant);
					float inv2a = 0.5f / a;

					float t1 = (-b - sqrt_d) * inv2a;
					float t2 = (-b + sqrt_d) * inv2a;

					float y1 = local_ray.origin.t[1] + t1 * local_ray.direction.t[1];
					float y2 = local_ray.origin.t[1] + t2 * local_ray.direction.t[1];

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
	return closest;
}

