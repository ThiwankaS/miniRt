/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 22:35:53 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/30 11:28:25 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

void	set_closet_hit_sp(t_object *object, t_hit *h, float *v)
{
	float	inv_2a;
	float	t1;
	float	t2;
	float	min_t;

	inv_2a = 0.5f / v[9];
	t1 = (-v[10] - v[13]) * inv_2a;
	t2 = (-v[10] + v[13]) * inv_2a;
	min_t = INFINITY;
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

void	find_hit_sphere(t_object *object, t_ray *r, t_hit *h)
{
	float	v[14];
	float 	radius_sq;

	radius_sq = object->radius * object->radius;
	v[0] = r->origin.t[0];
	v[1] = r->origin.t[1];
	v[2] = r->origin.t[2];
	v[3] = r->direction.t[0];
	v[4] = r->direction.t[1];
	v[5] = r->direction.t[2];
	v[6] = v[0] - 0;
	v[7] = v[1] - 0;
	v[8] = v[2] - 0;
	v[9] = v[3] * v[3] + v[4] * v[4] + v[5] * v[5];
	v[10] = 2.0f * (v[3] * v[6] + v[4] * v[7] + v[5] * v[8]);
	v[11] = v[6] * v[6] + v[7] * v[7] + v[8] * v[8] - radius_sq;
	v[12] = v[10] * v[10] - 4.0f * v[9] * v[11];
	if (v[12] >= 0.0f)
	{
		v[13] = sqrtf(v[12]);
		set_closet_hit_sp(object, h, v);
	}
}
