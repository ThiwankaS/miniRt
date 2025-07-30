/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 06:35:49 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/30 11:42:36 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

bool	get_position_pl(float *v, char *line)
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

bool	get_normal_pl(float *v, char *line)
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

bool	get_color_pl(float *v, char *line)
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

void	set_plane_values(t_state *state, t_object *s, float *v)
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
	s->ambient = state->world.ambient;
	s->diffuse = state->world.diffuse;
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
	if (!get_position_pl(v, items[0]))
		return (free_split(items), 1);
	if (!get_normal_pl(v, items[1]))
		return (free_split(items), 1);
	if (!get_color_pl(v, items[2]))
		return (free_split(items), 1);
	s = init_object();
	set_plane_values(state, s, v);
	free_split(items);
	return (0);
}
