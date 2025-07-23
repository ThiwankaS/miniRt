/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 02:26:59 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/23 05:44:50 by tsomacha         ###   ########.fr       */
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

void find_hit_sphere(t_object *object, t_ray *r, t_hit *h)
{
	float	v[14];

	// ray origin
	v[0] = r->origin.t[0];
	v[1] = r->origin.t[1];
	v[2] = r->origin.t[2];

	// ray direction
	v[3] = r->direction.t[0];
	v[4] = r->direction.t[1];
	v[5] = r->direction.t[2];

	// subtract sphere center from ray origin
	v[6] = v[0] - object->x;  // dx = origin.x - center.x
	v[7] = v[1] - object->y;  // dy = origin.y - center.y
	v[8] = v[2] - object->z;  // dz = origin.z - center.z

	// quadratic coefficients (a, b, c)
	v[9]  = v[3]*v[3] + v[4]*v[4] + v[5]*v[5];  // a = dot(direction, direction)
	v[10] = 2.0f * (v[3]*v[6] + v[4]*v[7] + v[5]*v[8]);  // b = 2 * dot(direction, sphere_to_ray)
	v[11] = v[6]*v[6] + v[7]*v[7] + v[8]*v[8] - (object->radius * object->radius);  // c = |sphere_to_ray|^2 - r^2

	// discriminant
	v[12] = v[10]*v[10] - 4.0f * v[9] * v[11];
	if (v[12] >= 0.0f)
	{
		v[13] = sqrtf(v[12]);
		float inv_2a = 0.5f / v[9];
		float t1 = (-v[10] - v[13]) * inv_2a;
		float t2 = (-v[10] + v[13]) * inv_2a;

		if (t1 > 0.0f && t1 < h->t)
		{
			h->t = t1;
			h->object = object;
			h->hit = true;
		}
		if (t2 > 0.0f && t2 < h->t)
		{
			h->t = t2;
			h->object = object;
			h->hit = true;
		}
	}
}


void find_hit_plane(t_object *object, t_ray *r, t_hit *h)
{
	float	dy;
	float	t;

	dy = r->direction.t[1];
	if (fabsf(dy) >= 1e-6f)
	{
		t = -r->origin.t[1] / dy;
		if (t > 0.0f && t < h->t)
		{
			h->t = t;
			h->object = object;
			h->hit = true;
		}
	}
}

void find_hit_cylinder(t_object *object, t_ray *r, t_hit *h)
{
	const float min_y = -1.0f;
	const float max_y =  1.0f;

	float ox = r->origin.t[0];
	float oz = r->origin.t[2];
	float dx = r->direction.t[0];
	float dz = r->direction.t[2];

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

			float y1 = r->origin.t[1] + t1 * r->direction.t[1];
			float y2 = r->origin.t[1] + t2 * r->direction.t[1];

			if (t1 > 0.0f && t1 < h->t && y1 >= min_y && y1 <= max_y)
			{
				h->t = t1;
				h->object = object;
				h->hit = true;
			}
			if (t2 > 0.0f && t2 < h->t && y2 >= min_y && y2 <= max_y)
			{
				h->t = t2;
				h->object = object;
				h->hit = true;
			}
		}
	}
}

t_hit find_hit(t_world *world, t_ray *ray)
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
		transform(&local_ray, ray, &object->invs);
		if (object->type == SPHERE)
			find_hit_sphere(object, &local_ray, &closest);
		// else if (object->type == PLANE)
		// 	find_hit_plane(object, &local_ray, &closest);
		// else if (object->type == CYLINDER)
		// 	find_hit_cylinder(object, &local_ray, &closest);
		object = object->next;
	}
	return closest;
}

