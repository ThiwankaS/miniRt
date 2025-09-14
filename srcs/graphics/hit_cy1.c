/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cy1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 22:35:40 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/04 04:00:13 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Chooses the nearest valid cylinder side hit from two quadratic roots and
 * updates the hit record if it's closer than the current one. Validity checks
 * require t > EPSILON and the y position to lie within the finite cylinder
 * bounds [v[6], v[7]].
 */
void	set_closet_hit_cy(t_object *object, t_hit *h, float *v)
{
	float	min_t;

	min_t = INFINITY;
	if (v[14] > EPSILON && v[16] >= v[6] && v[16] <= v[7])
		min_t = v[14];
	if (v[15] > EPSILON && v[17] >= v[6] && v[17] <= v[7])
	{
		if (v[15] < min_t)
		{
			min_t = v[15];
		}
	}
	if (min_t < h->t)
	{
		h->t = min_t;
		h->object = object;
		h->hit = true;
	}
}

/**
 * Caches ray origin/direction components into a temporary array and sets
 * constants used by the cylinder math: y-limits [-1, 1] and unit radius.
 * This avoids repeated struct access and magic numbers in later steps.
 */
void	cache_values(t_ray *r, float *v)
{
	v[0] = r->direction.t[0];
	v[1] = r->direction.t[1];
	v[2] = r->direction.t[2];
	v[3] = r->origin.t[0];
	v[4] = r->origin.t[1];
	v[5] = r->origin.t[2];
	v[6] = -1.0f;
	v[7] = 1.0f;
	v[8] = 1.0f;
}

/**
 * Computes the intersection of a ray with a finite unit cylinder aligned to the
 * y-axis, including caps. Solves the quadratic for the side surface, filters by
 * y-limits, updates the hit if closer, and always also tests the top/bottom
 * caps via hit_cap() when needed.
 */
void	find_hit_cylinder(t_object *object, t_ray *r, t_hit *h)
{
	float	v[18];

	cache_values(r, v);
	v[9] = v[0] * v[0] + v[2] * v[2];
	if (fabsf(v[9]) < EPSILON)
	{
		hit_cap(object, r, h);
		return ;
	}
	v[10] = 2.0f * v[3] * v[0] + 2.0f * v[5] * v[2];
	v[11] = v[3] * v[3] + v[5] * v[5] - v[8];
	v[12] = v[10] * v[10] - 4 * v[9] * v[11];
	if (v[12] < 0)
	{
		hit_cap(object, r, h);
		return ;
	}
	v[13] = sqrtf(v[12]);
	v[14] = (-v[10] - v[13]) / (2.0 * v[9]);
	v[15] = (-v[10] + v[13]) / (2.0 * v[9]);
	v[16] = v[4] + v[14] * v[1];
	v[17] = v[4] + v[15] * v[1];
	set_closet_hit_cy(object, h, v);
	hit_cap(object, r, h);
}
