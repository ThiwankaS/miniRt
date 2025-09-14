/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 04:38:17 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/27 15:38:12 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Parses an RGB color from a comma-separated string,
 * validates channels in [0,255],
 * stores the normalized color (0–1) into the world's light color.
 */
bool	set_light_color(t_world *world, char *line)
{
	float	v[3];

	if (!line)
		return (false);
	if (!extract_color(line, &v[0], &v[1], &v[2]))
		return (false);
	color(&world->light.color, v[0] / 255.0f, v[1] / 255.0f, v[2] / 255.0f);
	return (true);
}

/**
 * Parses the light's diffuse intensity from a string,
 * requiring a value in [0,1],
 * and stores it in the world.
 */
bool	set_light_diffuse(t_world *world, char *line)
{
	float	v;

	if (!line)
		return (false);
	if (!ft_atof(line, &v))
		return (false);
	if (v < 0.0f || v > 1.0f)
		return (false);
	world->diffuse = v;
	return (true);
}

/**
 * Parses a 3D position from a comma-separated string and assigns it to the
 * world's light position.
 */
bool	set_light_position(t_world *world, char *line)
{
	float	v[3];

	if (!line)
		return (false);
	if (!extract_position(line, &v[0], &v[1], &v[2]))
		return (false);
	point(&world->light.position, v[0], v[1], v[2]);
	return (true);
}

/**
 * Reads light position, diffuse intensity, and color from the input line,
 * validates each, and initializes the world's light once.
 * Returns nonzero on error.
 */
int	set_light(char *line, t_state *state, int *index)
{
	char	**items;

	if (state->world.set_light)
		return (0);
	items = ft_split(&line[*index], ' ');
	if (!items)
		return (free_split(items), 0);
	if (!set_light_position(&state->world, items[0]))
		return (free_split(items), 0);
	if (!set_light_diffuse(&state->world, items[1]))
		return (free_split(items), 0);
	if (items[2] && !set_light_color(&state->world, items[2]))
		return (free_split(items), 0);
	state->world.set_light = true;
	free_split(items);
	return (1);
}
