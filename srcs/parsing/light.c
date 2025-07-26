/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 04:38:17 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/22 21:50:00 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

bool	set_light_color(t_world *world, char *line)
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
	if (v[0] < 0.0f || v[0] > 255.0f)
		return (false);
	if (v[1] < 0.0f || v[1] > 255.0f)
		return (false);
	if (v[2] < 0.0f || v[2] > 255.0f)
		return (false);
	color(&world->light.color, v[0] / 255.0f, v[1] / 255.0f, v[2] / 255.0f);
	free_split(values);
	return (true);
}

bool	set_light_diffuse(t_world *world, char *line)
{
	float	v;

	if (!line)
		return (false);
	v = ft_atof(line);
	if (v < 0.0f || v > 1.0f)
		return (false);
	world->diffuse = v;
	return (true);
}

bool	set_light_position(t_world *world, char *line)
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
	point(&world->light.position, v[0], v[1], v[2]);
	free_split(values);
	return (true);
}

int	set_light(char *line, t_state *state, int *index)
{
	char	**items;

	if (state->world.set_light)
		return (1);
	items = ft_split(&line[*index], ' ');
	if (!items)
		return (free_split(items), 1);
	if (!set_light_position(&state->world, items[0]))
		return (free_split(items), 1);
	if (!set_light_diffuse(&state->world, items[1]))
		return (free_split(items), 1);
	if (!set_light_color(&state->world, items[2]))
		return (free_split(items), 1);
	state->world.set_light = true;
	free_split(items);
	return (0);
}
