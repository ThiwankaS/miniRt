/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 02:26:59 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/16 15:44:10 by tsomacha         ###   ########.fr       */
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

void find_hit_sphere(t_object *object, t_ray *r, t_hit *h)
{
	float	v[14];

	v[0] = r->origin.t[0];
	v[1] = r->origin.t[1];
	v[2] = r->origin.t[2];
	v[3] = r->direction.t[0];
	v[4] = r->direction.t[1];
	v[5] = r->direction.t[2];
	v[6] = v[3] * v[3] + v[4] * v[4] + v[5] * v[5];
	v[7] = 2.0f * (v[3] * v[0] + v[4] * v[1] + v[5] * v[2]);
	v[8] = v[0] * v[0] + v[1] * v[1] + v[2] * v[2] - 1.0f;
	v[9] = v[7] * v[7] - 4.0f * v[6] * v[8];
	if (v[9] >= 0.0f)
	{
		v[10] = sqrtf(v[9]);
		v[11] = 0.5f / v[6];
		v[12] = (-v[7] - v[10]) * v[11];
		v[13] = (-v[7] + v[10]) * v[11];
		if (v[12] > 0.0f && v[12] < h->t)
		{
			h->t = v[12];
			h->object = object;
			h->hit = true;
		}
		if (v[13] > 0.0f && v[13] < h->t)
		{
			h->t = v[13];
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
		else if (object->type == PLANE)
			find_hit_plane(object, &local_ray, &closest);
		else if (object->type == CYLINDER)
			find_hit_cylinder(object, &local_ray, &closest);
		object = object->next;
	}
	return closest;
}

