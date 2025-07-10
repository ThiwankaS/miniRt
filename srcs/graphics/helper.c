/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 01:59:36 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/10 05:41:16 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Sorts the linked list of intersections in ascending order by `t` value.
 * Uses a simple bubble sort algorithm.
 */
t_intersections	*intersections_sort(t_intersections *xs)
{
	int				swapped;
	t_intersections	*current;
	t_intersect		*temp;

	if (!xs || !xs->next)
		return (xs);
	while (1)
	{
		swapped = 0;
		current = xs;
		while (current && current->next)
		{
			if (current->intersect->value > current->next->intersect->value)
			{
				temp = current->intersect;
				current->intersect = current->next->intersect;
				current->next->intersect = temp;
				swapped = 1;
			}
			current = current->next;
		}
		if (!swapped)
			break ;
	}
	return (xs);
}

/**
 * Frees all memory allocated for a linked list of intersections,
 * including the intersection nodes.
 */
void	free_intersections(t_intersections *xs)
{
	t_intersections	*current;
	t_intersections	*temp;

	current = xs;
	while (current)
	{
		temp = current->next;
		free(current->intersect);
		free(current);
		current = temp;
	}
}

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
