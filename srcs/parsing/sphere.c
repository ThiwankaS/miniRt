/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 06:35:49 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/20 06:35:52 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

bool	get_position(float *v, char *line)
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

bool	get_radius(float *v, char *line)
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

bool	get_color(float *v, char *line)
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
	if (v[4] < 0.0f || v[4] > 255.0f)
		return (false);
	if (v[5] < 0.0f || v[5] > 255.0f)
		return (false);
	if (v[6] < 0.0f || v[6] > 255.0f)
		return (false);
	free_split(values);
	return (true);
}

void	set_sphere_values(t_state *state, t_object *s, float *v)
{
	if (!state || !s)
		return ;
	s->id = 1;
	s->type = 1;
	s->x = v[0];
	s->y = v[1];
	s->z = v[2];
	s->radius = v[3];
	color(&s->color, v[4], v[5], v[6]);
	s->ambient = state->world.ambient;
	s->diffuse = state->world.diffuse;
	s->specular = 0.0f;
	s->shininess = 200.0f;
	identity(&s->transform);
	identity(&s->invs);
	identity(&s->invs_trans);
	s->next = NULL;
	s->material = NULL;
	add_object(state, &s);
}

int	set_sphere(char *line, t_state *state, int *index)
{
	char		**items;
	float		v[7];
	t_object	*s;

	s = init_object();
	items = ft_split(&line[*index], ' ');
	if (!items)
		return (free_split(items), 1);
	if (!get_position(v, items[0]))
		return (free_split(items), 1);
	if (!get_radius(v, items[1]))
		return (free_split(items), 1);
	if (!get_color(v, items[2]))
		return (free_split(items), 1);
	set_sphere_values(state, s, v);
	free_split(items);
	return (0);
}
