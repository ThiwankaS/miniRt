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

int	init_world(t_world *world, float *v)
{
	if (world->set_ambient)
		return (1);
	if (v[0] < 0.0f || v[0] > 1.0f)
		return (1);
	if (v[1] < 0.0f || v[1] > 255.0f)
		return (1);
	if (v[2] < 0.0f || v[2] > 255.0f)
		return (1);
	if (v[3] < 0.0f || v[3] > 255.0f)
		return (1);
	world->ambient = v[0];
	color(&world->colour, v[1] / 255.0f, v[2] / 255.0f, v[3] / 255.0f);
	world->set_ambient = true;
	return (0);
}

bool	valid_char(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	if (c == '-')
		return (true);
	if (c == '.')
		return (true);
	return (false);
}

int	values_validation(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		else if (valid_char(str[i]))
		{
			i++;
			continue ;
		}
		else
			break ;
		i++;
	}
	if (count == 2 && (str[i] == '\0' || ft_isspace(str[i])))
		return (1);
	return (0);
}

int	set_world(char *line, t_state *state, int *index)
{
	char	**items;
	char	**values;
	float	v[4];

	items = ft_split(&line[*index], ' ');
	if (!items || !items[0] || !items[1])
		return (free_split(items), 1);
	if (!items[1] || !values_validation(items[1]))
		return (free_split(items), 1);
	values = ft_split(items[1], ',');
	if (!values || !values[0] || !values[1] || !values[2])
	{
		free_split(items);
		free_split(values);
		return (1);
	}
	v[0] = ft_atof(items[0]);
	v[1] = ft_atof(values[0]);
	v[2] = ft_atof(values[1]);
	v[3] = ft_atof(values[2]);
	free_split(items);
	free_split(values);
	if (init_world(&state->world, v))
		return (1);
	return (0);
}
