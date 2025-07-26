/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 02:25:18 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/23 04:28:44 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

bool	get_position_cy(float *v, char *line)
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

bool	get_normal_cy(float *v, char *line)
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

bool	get_radius_cy(float *v, char *line)
{
	float	d;

	if (!line)
		return (false);
	d = ft_atof(line);
	if (d < 0.0f)
		return (false);
	v[6] = d / 2.0f;
	return (true);
}

bool	get_height_cy(float *v, char *line)
{
	float	h;

	if (!line)
		return (false);
	h = ft_atof(line);
	if (h < 0.0f)
		return (false);
	v[7] = h;
	return (true);
}

bool	get_color_cy(float *v, char *line)
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
	v[8] = ft_atof(values[0]);
	v[9] = ft_atof(values[1]);
	v[10] = ft_atof(values[2]);
	free_split(values);
	if (v[8] < 0.0f || v[8] > 255.0f)
		return (false);
	if (v[9] < 0.0f || v[9] > 255.0f)
		return (false);
	if (v[10] < 0.0f || v[10] > 255.0f)
		return (false);
	return (true);
}
