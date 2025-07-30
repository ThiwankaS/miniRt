/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 06:35:49 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/30 11:42:17 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

bool	get_position_s(float *v, char *line)
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

bool	get_radius_s(float *v, char *line)
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

bool	get_color_s(float *v, char *line)
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

void	set_sphere_values(t_state *state, t_object *s, float *v)
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
	s->ambient = state->world.ambient;
	s->diffuse = state->world.diffuse;
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
	if (!get_position_s(v, items[0]))
		return (free_split(items), 1);
	if (!get_radius_s(v, items[1]))
		return (free_split(items), 1);
	if (!get_color_s(v, items[2]))
		return (free_split(items), 1);
	s = init_object();
	set_sphere_values(state, s, v);
	free_split(items);
	return (0);
}
