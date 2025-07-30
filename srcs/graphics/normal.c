/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 07:03:47 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/30 07:14:16 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

t_tuple	normal_at_cylinder(t_object *s, t_tuple *obj_p)
{
	float	dist;
	float	min;
	float	max;
	t_tuple	obj_normal;

	min = -s->height / 2.0f;
	max = s->height / 2.0f;
	dist = obj_p->t[0] * obj_p->t[0] + obj_p->t[2] * obj_p->t[2];
	if (dist < 1.0f && obj_p->t[1] >= max - EPSILON)
		vector(&obj_normal, 0.0f, 1.0f, 0.0f);
	else if (dist < 1.0f && obj_p->t[1] <= min + EPSILON)
		vector(&obj_normal, 0.0f, -1.0f, 0.0f);
	else
		vector(&obj_normal, obj_p->t[0], 0.0f, obj_p->t[2]);
	return (obj_normal);
}

t_tuple	normal_at(t_object *s, t_tuple *world_point)
{
	t_tuple	normal;
	t_tuple	obj_point;
	t_tuple	obj_normal;
	t_tuple	world_normal;
	t_tuple	absolute_point;

	point(&absolute_point, 0.0f, 0.0f, 0.0f);
	obj_point = matrix_multiply_by_tuple(&s->invs, world_point);
	if (s->type == PLANE)
		vector(&obj_normal, 0.0f, 1.0f, 0.0f);
	else if (s->type == SPHERE)
		obj_normal = tuple_subtract(&obj_point, &absolute_point);
	else if (s->type == CYLINDER)
		obj_normal = normal_at_cylinder(s, &obj_point);
	else
		vector(&obj_normal, 0.0f, 0.0f, 0.0f);
	world_normal = matrix_multiply_by_tuple(&s->invs_trans, &obj_normal);
	world_normal.t[3] = 0.0f;
	normal = normalize(&world_normal);
	return (normal);
}
