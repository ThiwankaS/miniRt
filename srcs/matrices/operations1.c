/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:43:39 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/18 06:00:26 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Initializes and returns a zero matrix (all elements = 0.0).
 */
t_mat	matrix(void)
{
	t_mat	m;
	int		row;
	int		column;

	column = 0;
	while (column < SIZE)
	{
		row = 0;
		while (row < SIZE)
		{
			m.m[column][row] = 0.0f;
			row++;
		}
		column++;
	}
	return (m);
}

/**
 * Prints the contents of a matrix in a formatted manner.
 */
void	matrix_print(t_mat *mt)
{
	int	row;
	int	column;

	column = 0;
	while (column < SIZE)
	{
		row = 0;
		while (row < SIZE)
		{
			printf(" | m[%d][%d] : %6.3f", column, row, mt->m[column][row]);
			row++;
		}
		printf("\n");
		column++;
	}
}

/**
 * Multiplies two matrices (m1 and m2) and returns the result.
 * Uses standard matrix multiplication logic.
 */
t_mat	matrix_multiply(t_mat *m1, t_mat *m2)
{
	t_mat	result;
	int		row;
	int		column;

	column = 0;
	while (column < SIZE)
	{
		row = 0;
		while (row < SIZE)
		{
			result.m[column][row] =
				m1->m[column][0] * m2->m[0][row] +
				m1->m[column][1] * m2->m[1][row] +
				m1->m[column][2] * m2->m[2][row] +
				m1->m[column][3] * m2->m[3][row];
			row++;
		}
		column++;
	}
	return (result);
}

/**
 * Returns an identity matrix (diagonal elements = 1, others = 0).
 */
t_mat	identity(void)
{
	t_mat	m = matrix();
	m.m[0][0] = 1.0f;
	m.m[1][1] = 1.0f;
	m.m[2][2] = 1.0f;
	m.m[3][3] = 1.0f;
	return (m);
}

/**
 * Transposes the given matrix (swaps rows with columns) and returns the result.
 */
t_mat	matrix_transpose(t_mat *m1)
{
	t_mat	result;
	int		row;
	int		column;

	column = 0;
	while (column < SIZE)
	{
		row = 0;
		while (row < SIZE)
		{
			result.m[column][row] = m1->m[row][column];
			row++;
		}
		column++;
	}
	return (result);
}
