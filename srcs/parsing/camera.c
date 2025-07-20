# include "../../include/miniRt.h"

void update_fov(t_camera *camera, float fov)
{
	float	half_view;
	float	aspect;
	float	hsize;
	float	vsize;

	hsize = camera->hsize;
	vsize = camera->vsize;
	camera->fov = fov;
	half_view = tan(fov/2);
	aspect = hsize /(float) vsize;
	if(aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	camera->pixel_size = (camera->half_width * 2) / camera->hsize;
}

void update_view(t_camera *camera, t_tuple *p, t_tuple *d)
{
	t_tuple from;
	t_tuple forward;
	t_tuple to;
	t_tuple up;

	point(&from, p->t[0], p->t[1], p->t[2]);
	vector(&forward, d->t[0], d->t[1], d->t[2]);
	vector(&up, 0.0f, 1.0f, 0.0f);
	tuple_add(&to, &from, &forward);
	view_transformation(camera, &from, &to, &up);
}

bool get_fov(float *fov, char *line)
{
	float	t;

	if (!line)
		return (false);
	t = ft_atof(line);
	if (t < 0.0f || t > 180.0f)
		return (false);
	*fov = t * (M_PI / 180.0f);
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
	free_split(values);
	if (v[0] < -1.0f || v[0] > 1.0f)
		return (false);
	if (v[1] < -1.0f || v[1] > 1.0f)
		return (false);
	if (v[2] < -1.0f || v[2] > 1.0f)
		return (false);
	if (v[0] == 0 && v[1] == 0 && v[2] == 0)
		return (false);
	vector(d, v[0], v[1], v[2]);
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
	t_tuple	p;
	t_tuple	d;
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
	update_fov(&state->camera, fov);
	update_view(&state->camera, &p, &d);
	state->camera.set_camera = true;
	free_split(items);
	return (0);
}
