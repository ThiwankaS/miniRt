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

/**
 * Parses cylinder diameter from a string and stores radius in v[6] (diameter/2).
 * Rejects negative values and invalid input.
 */
bool	get_radius_cy(float *v, char *line)
{
	float	d;

	if (!line)
		return (false);
	if (!ft_atof(line, &d))
		return (false);
	if (d < 0.0f)
		return (false);
	v[6] = d / 2.0f;
	return (true);
}

/**
 * Parses cylinder height from a string and stores it in v[7].
 * Rejects negative values and invalid input.
 */
bool	get_height_cy(float *v, char *line)
{
	float	h;

	if (!line)
		return (false);
	if (!ft_atof(line, &h))
		return (false);
	if (h < 0.0f)
		return (false);
	v[7] = h;
	return (true);
}
