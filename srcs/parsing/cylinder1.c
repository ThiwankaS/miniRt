/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 02:25:04 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/30 15:02:58 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

bool	get_position_cy(float *v, char *line);
bool	get_normal_cy(float *v, char *line);
bool	get_radius_cy(float *v, char *line);
bool	get_height_cy(float *v, char *line);
bool	get_color_cy(float *v, char *line);
t_mat	rotate_axis(t_tuple *axis, float angle);

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

void	creating_cylinder_object(t_object *s)
{
	t_tuple	v0;
	t_tuple	axis;
	t_mat	scale;
	t_mat	rotate;
	t_mat	traslate;

	vector(&v0, 0, 1, 0);
	axis = cross(&v0, &s->norm_v);
	scale = scaling(s->radius, s->height / 2.0f, s->radius);
	traslate = translation(s->x, s->y, s->z);
	rotate = set_rotate_matrix(s, &axis, &v0);
	scale = matrix_multiply(&rotate, &scale);
	s->transform = matrix_multiply(&traslate, &scale);
	matrix_inverse(&s->invs, &s->transform);
	s->invs_trans = matrix_transpose(&s->invs);
}

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

int	set_cylinder(char *line, t_state *state, int *index)
{
	char		**items;
	float		v[11];
	t_object	*s;

	items = ft_split(&line[*index], ' ');
	if (!items)
		return (free_split(items), 1);
	if (!get_position_cy(v, items[0]))
		return (free_split(items), 1);
	if (!get_normal_cy(v, items[1]))
		return (free_split(items), 1);
	if (!get_radius_cy(v, items[2]))
		return (free_split(items), 1);
	if (!get_height_cy(v, items[3]))
		return (free_split(items), 1);
	if (!get_color_cy(v, items[4]))
		return (free_split(items), 1);
	s = init_object();
	set_cylinder_values(state, s, v);
	creating_cylinder_object(s);
	free_split(items);
	return (0);
}
