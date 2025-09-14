/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 02:25:04 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/04 04:06:05 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

bool	get_radius_cy(float *v, char *line);
bool	get_height_cy(float *v, char *line);
t_mat	rotate_axis(t_tuple *axis, float angle);

/**
 * Creates a rotation matrix to align a cylinder's default up vector (v0) with
 * its specified normal vector. If the axis length is zero, rotation is either
 * identity or 180 degrees depending on direction.
 */
t_mat	set_rotate_matrix(t_object *s, t_tuple *axis, t_tuple *v0)
{
	float	angel;
	t_mat	rotate;

	if (tuple_magnitute(axis) == 0)
	{
		if (dot(v0, &s->norm_v) > 0)
			rotate = identity();
		else
			rotate = rotate_x(M_PI);
	}
	else
	{
		*axis = normalize(axis);
		angel = acosf(dot(v0, &s->norm_v));
		rotate = rotate_axis(axis, angel);
	}
	return (rotate);
}

/**
 * Builds the full transformation matrix for a cylinder object, including
 * scaling by radius/height, rotation to match the normal vector,
 * and translation to its position.
 * Also computes its inverse and inverse-transpose matrices.
 */
void	creating_cylinder_object(t_object *s, float radius)
{
	t_tuple	v0;
	t_tuple	axis;
	t_mat	scale;
	t_mat	rotate;
	t_mat	traslate;

	vector(&v0, 0, 1, 0);
	axis = cross(&v0, &s->norm_v);
	scale = scaling(radius, s->height / 2.0f, radius);
	traslate = translation(s->x, s->y, s->z);
	rotate = set_rotate_matrix(s, &axis, &v0);
	scale = matrix_multiply(&rotate, &scale);
	s->transform = matrix_multiply(&traslate, &scale);
	matrix_inverse(&s->invs, &s->transform);
	s->invs_trans = matrix_transpose(&s->invs);
}

/**
 * Initializes a cylinder object's properties from parsed values and adds it
 * to the world's object list. Sets material properties
 * and transformation defaults.
 */
void	set_cylinder_values(t_state *state, t_object *s, float *v)
{
	if (!state || !s)
		return ;
	s->id = 3;
	s->type = CYLINDER;
	s->x = v[0];
	s->y = v[1];
	s->z = v[2];
	vector(&s->norm_v, v[3], v[4], v[5]);
	s->norm_v = normalize(&s->norm_v);
	s->radius = v[6];
	s->height = v[7];
	color(&s->color, v[8] / 255.0f, v[9] / 255.0f, v[10] / 255.0f);
	s->ambient = &state->world.ambient;
	s->diffuse = &state->world.diffuse;
	s->specular = 0.0f;
	s->shininess = 200.0f;
	s->transform = identity();
	s->invs = identity();
	s->invs_trans = identity();
	s->next = NULL;
	add_object(state, &s);
	state->world.obj_count++;
}

/**
 * Parses cylinder parameters (position, normal, radius, height, color) from
 * a line of text, initializes the object, sets its values,
 * and applies transformations.
 * Returns nonzero on error.
 */
int	set_cylinder(char *line, t_state *state, int *index)
{
	char		**items;
	float		v[11];
	t_object	*s;

	items = ft_split(&line[*index], ' ');
	if (!items)
		return (free_split(items), 0);
	if (!extract_position(items[0], &v[0], &v[1], &v[2]))
		return (free_split(items), 0);
	if (!extract_normal_v(items[1], &v[3], &v[4], &v[5]))
		return (free_split(items), 0);
	if (!get_radius_cy(v, items[2]))
		return (free_split(items), 0);
	if (!get_height_cy(v, items[3]))
		return (free_split(items), 0);
	if (!extract_color(items[4], &v[8], &v[9], &v[10]))
		return (free_split(items), 0);
	s = init_object();
	set_cylinder_values(state, s, v);
	creating_cylinder_object(s, v[6]);
	free_split(items);
	return (1);
}
