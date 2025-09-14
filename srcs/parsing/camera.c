/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 04:38:29 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/27 15:38:28 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Updates the camera's field of view and recalculates its half-width,
 * half-height,
 * and pixel size based on aspect ratio. FOV is given in radians.
 */
void	update_fov(t_camera *camera, float fov)
{
	float	half_view;
	float	aspect;
	float	hsize;
	float	vsize;

	hsize = camera->hsize;
	vsize = camera->vsize;
	camera->fov = fov;
	half_view = tan(fov / 2);
	aspect = hsize / (float) vsize;
	if (aspect >= 1)
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

/**
 * Parses a field of view value from a string, validates it is in [0, 180],
 * and converts it from degrees to radians. Returns false on invalid input.
 */
bool	get_fov(float *fov, char *line)
{
	float	t;

	if (!line)
		return (false);
	if (!ft_atof(line, &t))
		return (false);
	if (t < 0.0f || t > 180.0f)
		return (false);
	*fov = t * (M_PI / 180.0f);
	return (true);
}

/**
 * Parses a 3D orientation vector from a comma-separated string, validates
 * its components are in [-1, 1] and not all zero, and stores it as a vector.
 */
bool	get_orientation(t_tuple *d, char *line)
{
	char	**values;
	float	v[3];

	if (!line)
		return (false);
	values = ft_split(line, ',');
	if (!values || !ft_atof(values[0], &v[0]) || !ft_atof(values[1], &v[1])
		|| !ft_atof(values[2], &v[2]))
	{
		free_split(values);
		return (false);
	}
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

/**
 * Parses a 3D point from a comma-separated string and stores it in
 * the given tuple.
 * Returns false if parsing or validation fails.
 */
bool	get_cordinates(t_tuple *p, char *line)
{
	char	**values;
	float	v[3];

	if (!line)
		return (false);
	values = ft_split(line, ',');
	if (!values || !ft_atof(values[0], &v[0]) || !ft_atof(values[1], &v[1])
		|| !ft_atof(values[2], &v[2]))
	{
		free_split(values);
		return (false);
	}
	point(p, v[0], v[1], v[2]);
	free_split(values);
	return (true);
}

/**
 * Reads and sets the camera's position, orientation,
 * and FOV from the input line.
 * Updates the camera's view parameters and marks it as set.
 * Returns nonzero on error.
 */
int	set_camera(char *line, t_state *state, int *index)
{
	char	**items;
	t_tuple	p;
	t_tuple	d;
	float	fov;

	if (state->camera.set_camera)
		return (0);
	items = ft_split(&line[*index], ' ');
	if (!items)
		return (free_split(items), 0);
	if (!get_cordinates(&p, items[0]))
		return (free_split(items), 0);
	if (!get_orientation(&d, items[1]))
		return (free_split(items), 0);
	if (!get_fov(&fov, items[2]))
		return (free_split(items), 0);
	update_fov(&state->camera, fov);
	update_view(&state->camera, &p, &d);
	state->camera.set_camera = true;
	free_split(items);
	return (1);
}
