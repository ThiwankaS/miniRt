#include "../../include/miniRt.h"

static bool	parse_position(float *v, char *line)
{
	char	**values;

	if (!line || !values_validation(line))
		return (false);
	values = ft_split(line, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		free_split(values);
		return (false);
	}
	v[0] = ft_atof(values[0]);
	v[1] = ft_atof(values[1]);
	v[2] = ft_atof(values[2]);
	free_split(values);
	return (true);
}

static bool	parse_orientation(float *v, char *line)
{
	char	**values;

	if (!line || !values_validation(line))
		return (false);
	values = ft_split(line, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		free_split(values);
		return (false);
	}
	v[3] = ft_atof(values[0]);
	v[4] = ft_atof(values[1]);
	v[5] = ft_atof(values[2]);
	free_split(values);
	if (v[3] < -1.0f || v[3] > 1.0f)
		return (false);
	if (v[4] < -1.0f || v[4] > 1.0f)
		return (false);
	if (v[5] < -1.0f || v[5] > 1.0f)
		return (false);
	return (true);
}

static bool	parse_radius(float *v, char *line)
{
	float	d;

	if (!line)
		return (false);
	d = ft_atof(line);
	if (d < 0.0f)
		return (false);
	v[6] = d / 2.0f;
	return (true);
}

static bool	parse_height(float *v, char *line)
{
	float	h;

	if (!line)
		return (false);
	h = ft_atof(line);
	if (h < 0.0f)
		return (false);
	v[7] = h;
	return (true);
}

static bool	parse_color_rgb(float *v, char *line)
{
	char	**values;

	if (!line || !values_validation(line))
		return (false);
	values = ft_split(line, ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		free_split(values);
		return (false);
	}
	v[8] = ft_atof(values[0]);
	v[9] = ft_atof(values[1]);
	v[10] = ft_atof(values[2]);
	free_split(values);
	if (v[8] < 0.0f || v[8] > 255.0f)
		return (false);
	if (v[9] < 0.0f || v[9] > 255.0f)
		return (false);
	if (v[10] < 0.0f || v[10] > 255.0f)
		return (false);
	return (true);
}

static t_mat	build_cylinder_rotation(t_object *s, t_tuple *axis, t_tuple *up_ref)
{
	float	angle;
	t_mat	rotate;

	if (tuple_magnitude(axis) == 0)
	{
		if (dot(up_ref, &s->norm_v) > 0)
			rotate = identity();
		else
			rotate = rotate_x(M_PI);
	}
	else
	{
		*axis = normalize(axis);
		angle = acosf(dot(up_ref, &s->norm_v));
		rotate = rotate_axis(axis, angle);
	}
	return (rotate);
}

void	creating_cylinder_object(t_object *s)
{
	t_tuple	up_ref;
	t_tuple	axis;
	t_mat	scale;
	t_mat	rotate;
	t_mat	translate;

	vector(&up_ref, 0, 1, 0);
	axis = cross(&up_ref, &s->norm_v);
	scale = scaling(s->radius, s->height / 2.0f, s->radius);
	translate = translation(s->x, s->y, s->z);
	rotate = build_cylinder_rotation(s, &axis, &up_ref);
	scale = matrix_multiply(&rotate, &scale);
	s->transform = matrix_multiply(&translate, &scale);
	matrix_inverse(&s->invs, &s->transform);
	s->invs_trans = matrix_transpose(&s->invs);
}

static void	apply_cylinder_to_world(t_state *state, t_object *s, float *v)
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
	if (!parse_position(v, items[0]))
		return (free_split(items), 1);
	if (!parse_orientation(v, items[1]))
		return (free_split(items), 1);
	if (!parse_radius(v, items[2]))
		return (free_split(items), 1);
	if (!parse_height(v, items[3]))
		return (free_split(items), 1);
	if (!parse_color_rgb(v, items[4]))
		return (free_split(items), 1);
	s = init_object();
	apply_cylinder_to_world(state, s, v);
	creating_cylinder_object(s);
	free_split(items);
	return (0);
}
