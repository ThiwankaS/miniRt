/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cy2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 00:24:42 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/30 00:59:16 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Checks if the ray intersection with the bottom cap of the cylinder
 * lies within the circular boundary. Updates hit data if valid.
 */
void	bottom_cap(t_object *object, t_hit *h, float *v)
{
	v[10] = v[3] + v[0] * v[9];
	v[11] = v[5] + v[2] * v[9];
	v[12] = v[10] * v[10] + v[11] * v[11];
	if (v[12] <= v[8])
	{
		h->t = v[9];
		h->object = object;
		h->hit = true;
	}
}

/**
 * Checks if the ray intersection with the top cap of the cylinder
 * lies within the circular boundary. Updates hit data if valid.
 */
void	top_cap(t_object *object, t_hit *h, float *v)
{
	v[10] = v[3] + v[0] * v[9];
	v[11] = v[5] + v[2] * v[9];
	v[12] = v[10] * v[10] + v[11] * v[11];
	if (v[12] <= v[8])
	{
		h->t = v[9];
		h->object = object;
		h->hit = true;
	}
}

/**
 * Tests a ray for intersection with the flat caps of a finite cylinder.
 * Calculates t for the bottom and top planes, then calls cap check functions
 * if the intersection point is within the circular radius.
 */
void	hit_cap(t_object *object, t_ray *r, t_hit *h)
{
	float	v[13];

	v[0] = r->direction.t[0];
	v[1] = r->direction.t[1];
	v[2] = r->direction.t[2];
	v[3] = r->origin.t[0];
	v[4] = r->origin.t[1];
	v[5] = r->origin.t[2];
	v[6] = -1.0f;
	v[7] = 1.0f;
	v[8] = 1.0f;
	if (fabsf(v[1]) > EPSILON)
	{
		v[9] = (v[6] - v[4]) / v[1];
		if (v[9] > EPSILON && v[9] < h->t)
			bottom_cap(object, h, v);
		v[9] = (v[7] - v[4]) / v[1];
		if (v[9] > EPSILON && v[9] < h->t)
			top_cap(object, h, v);
	}
}
