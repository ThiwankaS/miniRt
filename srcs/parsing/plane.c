/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 06:35:49 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/30 15:03:14 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Builds a rotation matrix around an arbitrary unit axis using Rodrigues'
 * rotation formula for the given angle in radians.
 */
t_mat	rotate_axis(t_tuple *axis, float angle)
{
	float	c;
	float	s;
	float	t;
	t_mat	rotate;

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

/**
 * Constructs a plane's transform by rotating the default up vector
 * to the plane's normal and translating to its position.
 * Also computes inverse and inverse-transpose.
 */
void	creating_plane_object(t_object *s)
{
	t_tuple	v0;
	t_tuple	axis;
	t_mat	rotate;
	t_mat	traslate;
	float	angel;

	vector(&v0, 0, 1, 0);
	axis = cross(&v0, &s->norm_v);
	if (tuple_magnitute(&axis) < EPSILON)
		rotate = rotate_x(M_PI);
	else
	{
		axis = normalize(&axis);
		angel = acosf(dot(&v0, &s->norm_v));
		rotate = rotate_axis(&axis, angel);
	}
	traslate = translation(s->x, s->y, s->z);
	s->transform = matrix_multiply(&traslate, &rotate);
	matrix_inverse(&s->invs, &s->transform);
	s->invs_trans = matrix_transpose(&s->invs);
}

/**
 * Initializes a plane object's fields from parsed values,
 * normalizes its normal,
 * sets material pointers, builds its transform, and adds it to the world.
 */
void	set_plane_values(t_state *state, t_object *s, float *v)
{
	if (!state || !s)
		return ;
	s->id = 2;
	s->type = PLANE;
	s->x = v[0];
	s->y = v[1];
	s->z = v[2];
	s->radius = 0.0f;
	s->height = 0.0f;
	color(&s->color, v[6] / 255.0f, v[7] / 255.0f, v[8] / 255.0f);
	vector(&s->norm_v, v[3], v[4], v[5]);
	s->norm_v = normalize(&s->norm_v);
	s->ambient = &state->world.ambient;
	s->diffuse = &state->world.diffuse;
	s->specular = 0.0f;
	s->shininess = 200.0f;
	s->transform = identity();
	s->invs = identity();
	s->invs_trans = identity();
	s->next = NULL;
	creating_plane_object(s);
	add_object(state, &s);
	state->world.obj_count++;
}

/**
 * Reads plane parameters (position, normal, color) from the input line,
 * creates and populates the plane object, and registers it with the world.
 * Returns nonzero on parsing or allocation error.
 */
int	set_plane(char *line, t_state *state, int *index)
{
	char		**items;
	float		v[9];
	t_object	*s;

	items = ft_split(&line[*index], ' ');
	if (!items)
		return (free_split(items), 0);
	if (!extract_position(items[0], &v[0], &v[1], &v[2]))
		return (free_split(items), 0);
	if (!extract_normal_v(items[1], &v[3], &v[4], &v[5]))
		return (free_split(items), 0);
	if (!extract_color(items[2], &v[6], &v[7], &v[8]))
		return (free_split(items), 0);
	s = init_object();
	set_plane_values(state, s, v);
	free_split(items);
	return (1);
}
