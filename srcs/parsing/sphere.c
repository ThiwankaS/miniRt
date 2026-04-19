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

static bool	parse_diameter(float *v, char *line)
{
	float	d;

	if (!line)
		return (false);
	d = ft_atof(line);
	if (d < 0.0f)
		return (false);
	v[3] = d / 2.0f;
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
	v[4] = ft_atof(values[0]);
	v[5] = ft_atof(values[1]);
	v[6] = ft_atof(values[2]);
	free_split(values);
	if (v[4] < 0.0f || v[4] > 255.0f)
		return (false);
	if (v[5] < 0.0f || v[5] > 255.0f)
		return (false);
	if (v[6] < 0.0f || v[6] > 255.0f)
		return (false);
	return (true);
}

void	creating_sphere_object(t_object *s)
{
	t_mat	scale;
	t_mat	translate;

	scale = scaling(s->radius, s->radius, s->radius);
	translate = translation(s->x, s->y, s->z);
	s->transform = matrix_multiply(&translate, &scale);
	matrix_inverse(&s->invs, &s->transform);
	s->invs_trans = matrix_transpose(&s->invs);
}

static void	apply_sphere_to_world(t_state *state, t_object *s, float *v)
{
	if (!state || !s)
		return ;
	s->id = 1;
	s->type = SPHERE;
	s->x = v[0];
	s->y = v[1];
	s->z = v[2];
	s->radius = v[3];
	s->height = 0.0f;
	color(&s->color, v[4] / 255.0f, v[5] / 255.0f, v[6] / 255.0f);
	vector(&s->norm_v, 0.0f, 0.0f, 0.0f);
	s->ambient = &state->world.ambient;
	s->diffuse = &state->world.diffuse;
	s->specular = 0.9f;
	s->shininess = 200.0f;
	s->next = NULL;
	creating_sphere_object(s);
	add_object(state, &s);
	state->world.obj_count++;
}

int	set_sphere(char *line, t_state *state, int *index)
{
	char		**items;
	float		v[7];
	t_object	*s;

	items = ft_split(&line[*index], ' ');
	if (!items)
		return (free_split(items), 1);
	if (!parse_position(v, items[0]))
		return (free_split(items), 1);
	if (!parse_diameter(v, items[1]))
		return (free_split(items), 1);
	if (!parse_color_rgb(v, items[2]))
		return (free_split(items), 1);
	s = init_object();
	apply_sphere_to_world(state, s, v);
	free_split(items);
	return (0);
}
