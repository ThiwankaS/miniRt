/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_pl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 22:35:47 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/29 23:02:53 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Calculates the intersection of a ray with an infinite horizontal plane
 * at y = 0.
 * If the ray is not parallel to the plane and the intersection is closer than
 * the current hit, updates the hit record with the new intersection data.
 */
void	find_hit_plane(t_object *object, t_ray *r, t_hit *h)
{
	float	t;

	if (fabsf(r->direction.t[1]) >= EPSILON)
	{
		t = -r->origin.t[1] / r->direction.t[1];
		if (t > EPSILON && t < h->t)
		{
			h->t = t;
			h->object = object;
			h->hit = true;
		}
	}
}
