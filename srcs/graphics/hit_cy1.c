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

void	cache_values(t_object *object, t_ray *r, float *v)
{
	v[0] = r->direction.t[0];
	v[1] = r->direction.t[1];
	v[2] = r->direction.t[2];
	v[3] = r->origin.t[0];
	v[4] = r->origin.t[1];
	v[5] = r->origin.t[2];
	v[6] = -object->height / 2.0f;
	v[7] = object->height / 2.0f;
	v[8] = object->radius * object->radius;
}

void	find_hit_cylinder(t_object *object, t_ray *r, t_hit *h)
{
	float	v[18];

	cache_values(object, r, v);
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
