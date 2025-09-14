/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 04:37:53 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/22 21:48:55 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Frees a NULL-terminated array of C strings and the array itself.
 * Safe to call with NULL; does nothing in that case.
 */
void	free_split(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/**
 * Initializes global ambient settings in the world from parsed values.
 * Validates ranges (ambient in [0,1], color channels in [0,255]) and
 * prevents re-initialization.
 */
int	init_world(t_world *world, float *v)
{
	if (world->set_ambient)
		return (0);
	world->ambient = v[0];
	color(&world->colour, v[1] / 255.0f, v[2] / 255.0f, v[3] / 255.0f);
	world->set_ambient = true;
	return (1);
}

/**
 * read, parse ambient color brigthness from the map and validate the
 * value
*/
bool	get_ambient_brigthness(float *v, const char *line)
{
	float	d;

	if (!ft_atof(line, &d))
		return (false);
	if (d < 0.0f || d > 1.0f)
		return (false);
	v[0] = d;
	return (true);
}

/**
 * Parses ambient light ratio and RGB color from the line, validates them,
 * and stores the normalized values in the world.
 * Returns nonzero on malformed input.
 */
int	set_world(char *line, t_state *state, int *index)
{
	char	**items;
	float	v[4];

	if (!line)
		return (0);
	items = ft_split(&line[*index], ' ');
	if (!items || !items[0] || !items[1])
		return (free_split(items), 0);
	if (!get_ambient_brigthness(v, items[0]))
		return (free_split(items), 0);
	if (!extract_color(items[1], &v[1], &v[2], &v[3]))
		return (free_split(items), 0);
	free_split(items);
	if (!init_world(&state->world, v))
		return (0);
	return (1);
}
