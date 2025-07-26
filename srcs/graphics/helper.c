/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 01:59:36 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/27 01:46:33 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

#include "../../include/miniRt.h"

/**
 * Returns a copy of the given 4x4 matrix.
 */
t_mat copy_matrix(t_mat *src)
{
	t_mat	dest;
	int		col;
	int		row;

	col = 0;
	while(col < SIZE)
	{
		row = 0;
		while(row < SIZE)
		{
			dest.m[col][row] = src->m[col][row];
			row++;
		}
		col++;
	}
	return (dest);
}

/**
 * Converts a tuple representing a color (with values in range 0.0–1.0)
 * into a packed 32-bit integer in RGBA format.
 */
uint32_t tuple_to_color(t_tuple *tp)
{
	uint32_t red = (uint32_t)(tp->t[0] * 255.0f);
	uint32_t green = (uint32_t)(tp->t[1] * 255.0f);
	uint32_t blue = (uint32_t)(tp->t[2] * 255.0f);
	uint32_t alpha = (uint32_t)(tp->t[3] * 255.0f);

	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}

/*
/**
 * Copies the contents of one 4x4 matrix (m2) into another (m1).
 */
void	set_transform(t_mat *m1, t_mat *m2)
{
	m1->m[0][0] = m2->m[0][0];
	m1->m[0][1] = m2->m[0][1];
	m1->m[0][2] = m2->m[0][2];
	m1->m[0][3] = m2->m[0][3];
	m1->m[1][0] = m2->m[1][0];
	m1->m[1][1] = m2->m[1][1];
	m1->m[1][2] = m2->m[1][2];
	m1->m[1][3] = m2->m[1][3];
	m1->m[2][0] = m2->m[2][0];
	m1->m[2][1] = m2->m[2][1];
	m1->m[2][2] = m2->m[2][2];
	m1->m[2][3] = m2->m[2][3];
	m1->m[3][0] = m2->m[3][0];
	m1->m[3][1] = m2->m[3][1];
	m1->m[3][2] = m2->m[3][2];
	m1->m[3][3] = m2->m[3][3];
}

/**
 * Converts a tuple representing a color (with values in range 0.0–1.0)
 * into a packed 32-bit integer in RGBA format.
 */
uint32_t	tuple_to_color(t_tuple *tp)
{
	uint32_t	red;
	uint32_t	green;
	uint32_t	blue;
	uint32_t	alpha;

	red = (uint32_t)(tp->t[0] * 255.0f);
	green = (uint32_t)(tp->t[1] * 255.0f);
	blue = (uint32_t)(tp->t[2] * 255.0f);
	alpha = (uint32_t)(tp->t[3] * 255.0f);
	return ((red << 24) | (green << 16) | (blue << 8) | alpha);
}
