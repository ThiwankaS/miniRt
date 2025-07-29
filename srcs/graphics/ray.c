/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 02:26:59 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/29 16:47:15 by tsomacha         ###   ########.fr       */
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
	v[6] = v[0] - 0;  // dx = origin.x - center.x
	v[7] = v[1] - 0;  // dy = origin.y - center.y
	v[8] = v[2] - 0;  // dz = origin.z - center.z

	// quadratic coefficients (a, b, c)
	v[9]  = v[3]*v[3] + v[4]*v[4] + v[5]*v[5];  // a = dot(direction, direction)
	v[10] = 2.0f * (v[3]*v[6] + v[4]*v[7] + v[5]*v[8]);  // b = 2 * dot(direction, sphere_to_ray)
	v[11] = v[6]*v[6] + v[7]*v[7] + v[8]*v[8] - 1;
	// discriminant
	v[12] = v[10]*v[10] - 4.0f * v[9] * v[11];
	if (v[12] >= 0.0f)
	{
		v[13] = sqrtf(v[12]);
		float inv_2a = 0.5f / v[9];
		float t1 = (-v[10] - v[13]) * inv_2a;
		float t2 = (-v[10] + v[13]) * inv_2a;

		float min_t = INFINITY;

		if (t1 > 0.0f && t1 < min_t)
			min_t = t1;
		if (t2 > 0.0f && t2 < min_t)
			min_t = t2;

		if (min_t < h->t)
		{
			h->t = min_t;
			h->object = object;
			h->hit = true;
		}
	}
}


void find_hit_plane(t_object *object, t_ray *r, t_hit *h)
{
	float	t;

	if (fabsf(r->direction.t[1]) >= EPSILON)
	{
		t = -r->origin.t[1] / r->direction.t[1];
		if ( t > EPSILON && t < h->t)
		{
			h->t = t;
			h->object = object;
			h->hit = true;
		}
	}
}


void hit_cap(t_object *object, t_ray *r, t_hit *h)
{
	float dx,dy,dz,ox,oy,oz,t,px,pz;
	float min, proc, max, radius_sq;

	dx = r->direction.t[0];
	dy = r->direction.t[1];
	dz = r->direction.t[2];
	ox = r->origin.t[0];
	oy = r->origin.t[1];
	oz = r->origin.t[2];
	min = -object->height / 2.0f;
	max =  object->height / 2.0f;
	radius_sq = object->radius * object->radius;
	if(fabsf(dy) > EPSILON)
	{
		t = (min - oy) / dy;
		if(t > EPSILON && t < h->t)
		{
			px = ox + dx * t;
			pz = oz + dz * t;
			proc = px * px + pz * pz;
			if(proc <= radius_sq)
			{
				h->t = t;
				h->object = object;
				h->hit = true;
			}
		}
		t = (max - oy) / dy;
		if(t > EPSILON && t < h->t)
		{
			px = ox + dx * t;
			pz = oz + dz * t;
			proc = px * px + pz * pz;
			if(proc <= radius_sq)
			{
				h->t = t;
				h->object = object;
				h->hit = true;
			}
		}
	}
}

void find_hit_cylinder(t_object *object, t_ray *r, t_hit *h)
{
	float dx,dy,dz,ox,oy,oz;
	float a,b,c,disc, sqrt_disc;
	float t1,t2,y1,y2, min_t;
	float min, max, radius_sq;

	min = -object->height / 2.0f;
	max =  object->height / 2.0f;
	dx = r->direction.t[0];
	dy = r->direction.t[1];
	dz = r->direction.t[2];
	ox = r->origin.t[0];
	oy = r->origin.t[1];
	oz = r->origin.t[2];
	radius_sq = object->radius * object->radius;
	a = dx * dx + dz * dz;
	if (fabsf(a) < EPSILON)
	{
		hit_cap(object, r, h);
		return ;
	}
	b = 2.0f * ox * dx + 2.0f * oz * dz;
	c = ox * ox + oz * oz - radius_sq; //have used radius instead of radius * radius  because radius = 1.0
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return ;
	sqrt_disc = sqrtf(disc);
	t1 = (-b - sqrt_disc) / (2.0 * a);
	t2 = (-b + sqrt_disc) / (2.0 * a);
	y1 = oy + t1 * dy;
	y2 = oy + t2 * dy;
	min_t = INFINITY;
	if (t1 > EPSILON && y1 >= min && y1 <= max)
		min_t = t1;
	if (t2 > EPSILON && y2 >= min && y2 <= max)
	{
		if (t2 < min_t)
		{
			min_t = t2;
		}
	}
	if (min_t < h->t)
	{
		h->t = min_t;
		h->object = object;
		h->hit = true;
	}
	hit_cap(object, r, h);
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
		local_ray = transform(ray, &object->invs);
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

