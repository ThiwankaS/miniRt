/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 06:04:34 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/09 06:07:10 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Creates a translation matrix that moves points by (x, y, z).
 * Stores the result in m0.
 */
void	translation(t_mat *m0, float x, float y, float z)
{
	indentity(m0);
	m0->m[0][3] = x;
	m0->m[1][3] = y;
	m0->m[2][3] = z;
}

/**
 * Creates a scaling matrix that scales along x, y, and z axes.
 * Stores the result in m0.
 */
void	scalling(t_mat *m0, float x, float y, float z)
{
	indentity(m0);
	m0->m[0][0] = x;
	m0->m[1][1] = y;
	m0->m[2][2] = z;
}

/**
 * Creates a rotation matrix around the X-axis by angle r (in radians).
 * Stores the result in m0.
 */
void	rotate_x(t_mat *m0, float r)
{
	float	v1;
	float	v2;

	v1 = cos(r);
	v2 = sin(r);
	indentity(m0);
	m0->m[1][1] = v1;
	m0->m[1][2] = -v2;
	m0->m[2][1] = v2;
	m0->m[2][2] = v1;
}

/**
 * Creates a rotation matrix around the Y-axis by angle r (in radians).
 * Stores the result in m0.
 */
void	rotate_y(t_mat *m0, float r)
{
	float	v1;
	float	v2;

	v1 = cos(r);
	v2 = sin(r);
	indentity(m0);
	m0->m[0][0] = v1;
	m0->m[0][2] = v2;
	m0->m[2][0] = -v2;
	m0->m[2][2] = v1;
}

/**
 * Creates a rotation matrix around the Z-axis by angle r (in radians).
 * Stores the result in m0.
 */
void	rotate_z(t_mat *m0, float r)
{
	float	v1;
	float	v2;

	v1 = cos(r);
	v2 = sin(r);
	indentity(m0);
	m0->m[0][0] = v1;
	m0->m[0][1] = -v2;
	m0->m[1][0] = v2;
	m0->m[1][1] = v1;
}
