# include "../../include/miniRt.h"

bool get_fov(float *fov, char *line)
{
	float	t;

	if (!line)
		return (false);
	t = ft_atof(line);
	if (t < 0.0f || t > 180.0f)
		return (false);
	*fov = t;
	return (true);
}

bool get_orientation(t_tuple *d, char *line)
{
	char	**values;
	float	v[3];

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
	if (v[0] < -1.0f || v[0] > 1.0f)
		return (false);
	if (v[1] < -1.0f || v[1] > 1.0f)
		return (false);
	if (v[2] < -1.0f || v[2] > 1.0f)
		return (false);
	vector(d, v[0], v[1], v[2]);
	free_split(values);
	return (true);
}

bool get_cordinates(t_tuple *p, char *line)
{
	char	**values;
	float	v[3];

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
	point(p, v[0], v[1], v[2]);
	free_split(values);
	return (true);
}

int set_camera(char *line, t_state *state, int *index)
{
	char	**items;
	t_tuple p;
	t_tuple d;
	float	fov;

	if (state->camera.set_camera)
		return (1);
	items = ft_split(&line[*index],' ');
	if (!items)
		return (free_split(items), 1);
	if(!get_cordinates(&p, items[0]))
		return (free_split(items), 1);
	if(!get_orientation(&d, items[1]))
		return (free_split(items), 1);
	if(!get_fov(&fov, items[2]))
		return (free_split(items), 1);
	state->camera.set_camera = true;
	free_split(items);
	return (0);
}
