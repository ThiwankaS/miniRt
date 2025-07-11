/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:43:39 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/11 04:07:59 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Initializes all elements of a matrix to 0.0.
 */
void	matrix(t_mat *m)
{
	int	row;
	int	column;

	row = 0;
	column = 0;
	while (column < SIZE)
	{
		row = 0;
		while (row < SIZE)
		{
			m->m[column][row] = 0.0;
			row++;
		}
		column++;
	}
}

/**
 * Prints the contents of a matrix in a formatted manner.
 */
void	matrix_print(t_mat *mt)
{
	int	row;
	int	column;

	row = 0;
	column = 0;
	while (column < SIZE)
	{
		row = 0;
		while (row < SIZE)
		{
			printf(" | m[%d][%d] : %8.5f", column, row, mt->m[column][row]);
			row++;
		}
		printf("\n");
		column++;
	}
}

/**
 * Multiplies two matrices (m1 and m2) and stores the result in m0.
 * Uses standard matrix multiplication logic.
 */
void	matrix_multiply(t_mat *m0, t_mat *m1, t_mat *m2)
{
	int	column;
	int	row;
	int	k;

	column = 0;
	while (column < SIZE)
	{
		row = 0;
		while (row < SIZE)
		{
			m0->m[column][row] = 0.0;
			k = 0;
			while (k < SIZE)
			{
				m0->m[column][row] += m1->m[column][k] * m2->m[k][row];
				k++;
			}
			row++;
		}
		column++;
	}
}

/**
 * Sets a matrix to the identity matrix (diagonal elements = 1, others = 0).
 */
void	identity(t_mat *m0)
{
	matrix(m0);
	m0->m[0][0] = 1.0;
	m0->m[1][1] = 1.0;
	m0->m[2][2] = 1.0;
	m0->m[3][3] = 1.0;
}

/**
 * Transposes a matrix m1 and stores the result in m0.
 * Swaps rows with columns.
 */
void	matrix_transpose(t_mat *m0, t_mat *m1)
{
	int	row;
	int	column;

	row = 0;
	column = 0;
	while (column < SIZE)
	{
		row = 0;
		while (row < SIZE)
		{
			m0->m[column][row] = m1->m[row][column];
			row++;
		}
		column++;
	}
}
