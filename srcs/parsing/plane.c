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
	v[6] = ft_atof(values[0]);
	v[7] = ft_atof(values[1]);
	v[8] = ft_atof(values[2]);
	free_split(values);
	if (v[6] < 0.0f || v[6] > 255.0f)
		return (false);
	if (v[7] < 0.0f || v[7] > 255.0f)
		return (false);
	if (v[8] < 0.0f || v[8] > 255.0f)
		return (false);
	return (true);
}

void	creating_plane_object(t_object *s)
{
	t_tuple	default_up;
	t_tuple	axis;
	t_mat	rotate;
	t_mat	translate;
	float	angle;

	vector(&default_up, 0, 1, 0);
	axis = cross(&default_up, &s->norm_v);
	if (tuple_magnitude(&axis) == 0)
	{
		if (dot(&default_up, &s->norm_v) > 0)
			rotate = identity();
		else
			rotate = rotate_x(M_PI);
	}
	else
	{
		axis = normalize(&axis);
		angle = acosf(dot(&default_up, &s->norm_v));
		rotate = rotate_axis(&axis, angle);
	}
	translate = translation(s->x, s->y, s->z);
	s->transform = matrix_multiply(&translate, &rotate);
	matrix_inverse(&s->invs, &s->transform);
	s->invs_trans = matrix_transpose(&s->invs);
}

static void	apply_plane_to_world(t_state *state, t_object *s, float *v)
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

int	set_plane(char *line, t_state *state, int *index)
{
	char		**items;
	float		v[9];
	t_object	*s;

	items = ft_split(&line[*index], ' ');
	if (!items)
		return (free_split(items), 1);
	if (!parse_position(v, items[0]))
		return (free_split(items), 1);
	if (!parse_orientation(v, items[1]))
		return (free_split(items), 1);
	if (!parse_color_rgb(v, items[2]))
		return (free_split(items), 1);
	s = init_object();
	apply_plane_to_world(state, s, v);
	free_split(items);
	return (0);
}
