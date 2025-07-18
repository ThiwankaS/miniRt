/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:47:32 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/16 15:30:34 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Multiplies a matrix (m0) with a tuple (t1) and stores the result in t0.
 * Each component of the result is computed as a dot product of a matrix row
 * and the tuple.
 */
void	matrix_multiply_by_tuple(t_tuple *t0, t_mat *m0, t_tuple *t1)
{
	t0->t[0] = m0->m[0][0] * t1->t[0] + m0->m[0][1] * t1->t[1]
				+ m0->m[0][2] * t1->t[2] + m0->m[0][3] * t1->t[3];
	t0->t[1] = m0->m[1][0] * t1->t[0] + m0->m[1][1] * t1->t[1]
				+ m0->m[1][2] * t1->t[2] + m0->m[1][3] * t1->t[3];
	t0->t[2] = m0->m[2][0] * t1->t[0] + m0->m[2][1] * t1->t[1]
				+ m0->m[2][2] * t1->t[2] + m0->m[2][3] * t1->t[3];
	t0->t[3] = m0->m[3][0] * t1->t[0] + m0->m[3][1] * t1->t[1]
				+ m0->m[3][2] * t1->t[2] + m0->m[3][3] * t1->t[3];
}

/**
 * Computes the determinant of a 2x2 matrix.
 */
float	det2x2(t_mat2 *m0)
{
	float	result;

	result = 0.0;
	result = m0->m[0][0] * m0->m[1][1] - m0->m[0][1] * m0->m[1][0];
	return (result);
}

/**
 * Extracts a 3x3 submatrix (m0) from a 4x4 matrix (m1),
 * removing the specified column and row.
 */
void	submatrix4x4(t_mat3 *m0, t_mat *m1, int column, int row)
{
	int	i;
	int	j;
	int	si;
	int	sj;

	i = 0;
	si = 0;
	while (i < SIZE)
	{
		if (i == column)
		{
			i++;
			continue ;
		}
		j = 0;
		sj = 0;
		while (j < SIZE)
		{
			if (j != row)
				m0->m[si][sj++] = m1->m[i][j];
			j++;
		}
		si++;
		i++;
	}
}

/**
 * Extracts a 2x2 submatrix (m0) from a 3x3 matrix (m1),
 * removing the specified column and row.
 */
void	submatrix3x3(t_mat2 *m0, t_mat3 *m1, int column, int row)
{
	int	i;
	int	j;
	int	si;
	int	sj;

	i = 0;
	si = 0;
	while (i < SIZE - 1)
	{
		if (i == column)
		{
			i++;
			continue ;
		}
		j = 0;
		sj = 0;
		while (j < SIZE -1)
		{
			if (j != row)
				m0->m[si][sj++] = m1->m[i][j];
			j++;
		}
		si++;
		i++;
	}
}

/**
 * Computes the minor of a 3x3 matrix at the given column and row.
 * A minor is the determinant of the submatrix after removing
 * the given row and column.
 */
float	minor(t_mat3 *m0, int column, int row)
{
	float	result;
	t_mat2	m2;

	result = 0.0;
	submatrix3x3(&m2, m0, column, row);
	result = det2x2(&m2);
	return (result);
}
