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
 * and returns the result.
 */
t_tuple	tuple_add(t_tuple *t1, t_tuple *t2)
{
	t_tuple	result;

	result.t[0] = t1->t[0] + t2->t[0];
	result.t[1] = t1->t[1] + t2->t[1];
	result.t[2] = t1->t[2] + t2->t[2];
	result.t[3] = t1->t[3] + t2->t[3];
	return (result);
}

/**
 * Subtracts components of tuple t2 from tuple t1
 * and returns the result.
 */
t_tuple	tuple_subtract(t_tuple *t1, t_tuple *t2)
{
	t_tuple	result;

	result.t[0] = t1->t[0] - t2->t[0];
	result.t[1] = t1->t[1] - t2->t[1];
	result.t[2] = t1->t[2] - t2->t[2];
	result.t[3] = t1->t[3] - t2->t[3];
	return (result);
}

/**
 * Negates a tuple by subtracting it from a zero vector
 * and returns the result.
 */
t_tuple	tuple_negate(t_tuple *t2)
{
	t_tuple	zero;

	vector(&zero, 0.0, 0.0, 0.0);
	return (tuple_subtract(&zero, t2));
}

/**
 * Multiplies each component of tuple t1 by scalar 'a'
 * and returns the result.
 */
t_tuple	tuple_multiply_scalar(t_tuple *t1, float a)
{
	t_tuple	result;

	result.t[0] = t1->t[0] * a;
	result.t[1] = t1->t[1] * a;
	result.t[2] = t1->t[2] * a;
	result.t[3] = t1->t[3] * a;
	return (result);
}

/**
 * Divides each component of tuple t1 by scalar 'a'
 * and returns the result. If 'a' is zero, returns a zero tuple.
 */
t_tuple	tuple_divide_scalar(t_tuple *t1, float a)
{
	if (a == 0.0f)
		return ((t_tuple){{0.0, 0.0, 0.0, 0.0}});
	return (tuple_multiply_scalar(t1, 1.0f / a));
}

