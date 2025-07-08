/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:21:24 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/08 20:25:58 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Adds corresponding components of two tuples (t1 and t2)
 * and stores the result in t0.
 */
void	tuple_add(t_tuple *t0, t_tuple *t1, t_tuple *t2)
{
	t0->t[0] = t1->t[0] + t2->t[0];
	t0->t[1] = t1->t[1] + t2->t[1];
	t0->t[2] = t1->t[2] + t2->t[2];
	t0->t[3] = t1->t[3] + t2->t[3];
}

/**
 * Subtracts components of tuple t2 from tuple t1
 * and stores the result in t0.
 */
void	tuple_subtract(t_tuple *t0, t_tuple *t1, t_tuple *t2)
{
	t0->t[0] = t1->t[0] - t2->t[0];
	t0->t[1] = t1->t[1] - t2->t[1];
	t0->t[2] = t1->t[2] - t2->t[2];
	t0->t[3] = t1->t[3] - t2->t[3];
}

/**
 * Negates a tuple by subtracting it from a zero vector.
 * Stores the result in t1.
 */
void	tuple_negate(t_tuple *t1, t_tuple *t2)
{
	t_tuple	zero;

	vector(&zero, 0.0, 0.0, 0.0);
	tuple_subtract(t1, &zero, t2);
}

/**
 * Multiplies each component of tuple t1 by scalar 'a'
 * and stores the result in t0.
 */
void	tuple_multiply_scalor(t_tuple *t0, t_tuple *t1, float a)
{
	t0->t[0] = t1->t[0] * a;
	t0->t[1] = t1->t[1] * a;
	t0->t[2] = t1->t[2] * a;
	t0->t[3] = t1->t[3] * a;
}

/**
 * Divides each component of tuple t1 by scalar 'a'
 * and stores the result in t0. If 'a' is zero, t0 is set to zero tuple.
 */
void	tuple_divide_scalor(t_tuple *t0, t_tuple *t1, float a)
{
	float	b;

	if (a == 0.0)
	{
		t0->t[0] = 0.0;
		t0->t[1] = 0.0;
		t0->t[2] = 0.0;
		t0->t[3] = 0.0;
	}
	b = 1 / a;
	tuple_multiply_scalor(t0, t1, b);
}
