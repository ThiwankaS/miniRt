/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:54:00 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/09 10:39:15 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Computes the cofactor of a 3x3 matrix at the specified row and column.
 * Applies sign based on position: cofactor = ±minor depending on (row + column).
 */
float	matrix_cofactor(t_mat3 *m0, int row, int column)
{
	float	det;

	det = minor(m0, row, column);
	if ((row + column) % 2 != 0)
		det = det * -1;
	return (det);
}

/**
 * Computes the determinant of a 3x3 matrix using cofactor expansion.
 */
float	det3x3(t_mat3 *m)
{
	float	det;

	det = 0.0;
	det += m->m[0][0] * matrix_cofactor(m, 0, 0);
	det += m->m[0][1] * matrix_cofactor(m, 0, 1);
	det += m->m[0][2] * matrix_cofactor(m, 0, 2);
	return (det);
}

/**
 * Computes the determinant of a 4x4 matrix using cofactor expansion along
 * the first row.
 */
float	det4x4(t_mat *m)
{
	int		j;
	float	det;
	float	cofactor;
	t_mat3	sub;

	j = 0;
	det = 0.0;
	while (j < SIZE)
	{
		submatrix4x4(&sub, m, 0, j);
		cofactor = det3x3(&sub);
		if (j % 2 != 0)
			cofactor = -cofactor;
		det += m->m[0][j] * cofactor;
		j++;
	}
	return (det);
}

/**
 * Calculates the inverse of a 4x4 matrix using the adjugate and determinant.
 * Returns true if the inverse exists, false if the matrix is
 * non-invertible (det = 0).
 */
bool	matrix_inverse(t_mat *out, t_mat *in)
{
	int		row;
	int		col;
	float	det;
	float	cofactor;
	t_mat3	sub;

	det = det4x4(in);
	if (det == 0.0)
		return (false);
	row = 0;
	while (row < SIZE)
	{
		col = 0;
		while (col < SIZE)
		{
			submatrix4x4(&sub, in, row, col);
			cofactor = det3x3(&sub);
			if ((row + col) % 2 != 0)
				cofactor = -cofactor;
			out->m[col][row] = cofactor / det;
			col++;
		}
		row++;
	}
	return (true);
}

void transform(t_ray *rp, t_ray *r, t_mat *m)
{
	matrix_multiply_by_tuple(&rp->origin, m, &r->origin);
	matrix_multiply_by_tuple(&rp->direction, m, &r->direction);
}
