/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader2.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 04:38:04 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/02 15:06:18 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Validates a comma-separated triple "x,y,z" with only numeric chars,
 * '-' and '.'.
 * Requires exactly two commas and allows end-of-string or whitespace after
 * the triple.
 */
bool	is_valid(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_strchr(CHAR_LIST, str[i]))
			i++;
		else
			return (false);
	}
	return (true);
}

/*
 * Validates and processes a line of scene data.
 * Returns true if the line is valid and processed successfully,
 * otherwise returns false.
*/
bool	extract_data(char *line, t_state *state)
{
	if (!is_valid(line))
		return (false);
	if (process_line(line, state) == 0)
		return (false);
	return (true);
}

/*
 * Extracts RGB color values from a string formatted as "R,G,B".
 * Ensures each component is a valid number between 0 and 255.
 * Returns true on success, false otherwise.
*/
bool	extract_color(char *line, float *r, float *g, float *b)
{
	char	**values;

	values = ft_split(line, ',');
	if (!values || !ft_atof(values[0], r) || !ft_atof(values[1], g)
		|| !ft_atof(values[2], b))
	{
		free_split(values);
		return (false);
	}
	free_split(values);
	if (*r < 0.0f || *r > 255.0f)
		return (false);
	if (*g < 0.0f || *g > 255.0f)
		return (false);
	if (*b < 0.0f || *b > 255.0f)
		return (false);
	return (true);
}

/*
 * Extracts position coordinates from a string formatted as "x,y,z".
 * Returns true if all three values are successfully parsed,
 * otherwise returns false.
*/
bool	extract_position(char *line, float *x, float *y, float *z)
{
	char	**values;

	if (!line)
		return (false);
	values = ft_split(line, ',');
	if (!values || !ft_atof(values[0], x) || !ft_atof(values[1], y)
		|| !ft_atof(values[2], z))
	{
		free_split(values);
		return (false);
	}
	free_split(values);
	return (true);
}

/*
 * Extracts a normalized vector from a string formatted as "x,y,z".
 * Ensures each component is within [-1, 1] and not all zero.
 * Returns true if valid, false otherwise.
*/
bool	extract_normal_v(char *line, float *x, float *y, float *z)
{
	char	**values;

	if (!line)
		return (false);
	values = ft_split(line, ',');
	if (!values || !ft_atof(values[0], x) || !ft_atof(values[1], y)
		|| !ft_atof(values[2], z))
	{
		free_split(values);
		return (false);
	}
	free_split(values);
	if (*x < -1.0f || *x > 1.0f)
		return (false);
	if (*y < -1.0f || *y > 1.0f)
		return (false);
	if (*z < -1.0f || *z > 1.0f)
		return (false);
	if (*x == 0.0f && *y == 0.0f && *z == 0.0f)
		return (false);
	return (true);
}
