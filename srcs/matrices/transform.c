/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 06:04:34 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/11 04:20:59 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Creates and returns a translation matrix that moves points by (x, y, z).
 */
t_mat	translation(float x, float y, float z)
{
	t_mat m = identity();
	m.m[0][3] = x;
	m.m[1][3] = y;
	m.m[2][3] = z;
	return (m);
}

/**
 * Creates and returns a scaling matrix that scales along x, y, and z axes.
 */
t_mat	scaling(float x, float y, float z)
{
	t_mat m = identity();
	m.m[0][0] = x;
	m.m[1][1] = y;
	m.m[2][2] = z;
	return (m);
}

/**
 * Creates and returns a rotation matrix around the X-axis by angle r (in radians).
 */
t_mat	rotate_x(float r)
{
	t_mat m = identity();
	float v1 = cos(r);
	float v2 = sin(r);

	m.m[1][1] = v1;
	m.m[1][2] = -v2;
	m.m[2][1] = v2;
	m.m[2][2] = v1;
	return (m);
}

/**
 * Creates and returns a rotation matrix around the Y-axis by angle r (in radians).
 */
t_mat	rotate_y(float r)
{
	t_mat m = identity();
	float v1 = cos(r);
	float v2 = sin(r);

	m.m[0][0] = v1;
	m.m[0][2] = v2;
	m.m[2][0] = -v2;
	m.m[2][2] = v1;
	return (m);
}

/**
 * Creates and returns a rotation matrix around the Z-axis by angle r (in radians).
 */
t_mat	rotate_z(float r)
{
	t_mat m = identity();
	float v1 = cos(r);
	float v2 = sin(r);

	m.m[0][0] = v1;
	m.m[0][1] = -v2;
	m.m[1][0] = v2;
	m.m[1][1] = v1;
	return (m);
}

