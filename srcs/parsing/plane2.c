/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 07:49:12 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/29 10:10:07 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

t_mat rotate_axis(t_tuple *axis, float angle)
{
	float c;
	float s;
	float t;
	t_mat rotate;

	c = cosf(angle);
	s = sinf(angle);
	t = 1.0f - c;
	rotate = identity();
	rotate.m[0][0] = t * axis->t[0] * axis->t[0] + c;
	rotate.m[0][1] = t * axis->t[0] * axis->t[1] - s * axis->t[2];
	rotate.m[0][2] = t * axis->t[0] * axis->t[2] + s * axis->t[1];
	rotate.m[1][0] = t * axis->t[0] * axis->t[1] + s * axis->t[2];
	rotate.m[1][1] = t * axis->t[1] * axis->t[1] + c;
	rotate.m[1][2] = t * axis->t[1] * axis->t[2] - s * axis->t[0];
	rotate.m[2][0] = t * axis->t[0] * axis->t[2] - s * axis->t[1];
	rotate.m[2][1] = t * axis->t[1] * axis->t[2] + s * axis->t[0];
	rotate.m[2][2] = t * axis->t[2] * axis->t[2] + c;
	return (rotate);
}

void	creating_plane_object(t_object *s)
{
	t_tuple	v0;
	t_tuple	axis;
	t_mat	rotate;
	t_mat	traslate;
	float	angel;

	vector(&v0, 0, 1, 0);
	axis = cross(&v0, &s->norm_v);
	axis = normalize(&axis);
	angel = acos(dot(&v0, &s->norm_v));
	rotate = rotate_axis(&axis, angel);
	traslate = translation(s->x, s->y, s->z);
	s->transform = matrix_multiply(&traslate, &rotate);
	matrix_inverse(&s->invs, &s->transform);
	s->invs_trans = matrix_transpose(&s->invs);
}
