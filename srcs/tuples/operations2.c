/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:28:36 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/29 20:40:29 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Calculates the magnitude (length) of a tuple vector.
 * Uses the Euclidean norm: sqrt(x² + y² + z² + w²).
 * Returns the computed magnitude as a float.
 */
float	tuple_magnitute(t_tuple *t0)
{
	float	x_squared;
	float	y_squared;
	float	z_squared;
	float	w_squared;

	x_squared = t0->t[0] * t0->t[0];
	y_squared = t0->t[1] * t0->t[1];
	z_squared = t0->t[2] * t0->t[2];
	w_squared = t0->t[3] * t0->t[3];
	return (sqrtf(x_squared + y_squared + z_squared + w_squared));
}

/**
 * Computes the dot product of two tuples (t1 and t2).
 * Returns the scalar result of: x1*x2 + y1*y2 + z1*z2 + w1*w2.
 */
float	dot(t_tuple *t1, t_tuple *t2)
{
	float	sum;

	sum = 0.0f;
	sum += t1->t[0] * t2->t[0];
	sum += t1->t[1] * t2->t[1];
	sum += t1->t[2] * t2->t[2];
	sum += t1->t[3] * t2->t[3];
	return (sum);
}

/**
 * Normalizes the given tuple (t1).
 * A normalized vector has magnitude 1 and points in the same direction.
 * Returns the normalized tuple.
 */
t_tuple	normalize(t_tuple *t1)
{
	float	mag;

	mag = tuple_magnitute(t1);
	return (tuple_divide_scalar(t1, mag));
}

/**
 * Computes the cross product of two vectors (t1 and t2).
 * Only the x, y, z components are used; w is set to 0.0.
 * Returns the resulting vector.
 */
t_tuple	cross(t_tuple *t1, t_tuple *t2)
{
	t_tuple	result;

	result.t[0] = t1->t[1] * t2->t[2] - t1->t[2] * t2->t[1];
	result.t[1] = t1->t[2] * t2->t[0] - t1->t[0] * t2->t[2];
	result.t[2] = t1->t[0] * t2->t[1] - t1->t[1] * t2->t[0];
	result.t[3] = 0.0;
	return (result);
}

/**
 * Performs the Schur (Hadamard) product — element-wise multiplication
 * of two tuples. Returns the resulting tuple.
 */
t_tuple	schur_product(t_tuple *t1, t_tuple *t2)
{
	t_tuple	result;

	result.t[0] = t1->t[0] * t2->t[0];
	result.t[1] = t1->t[1] * t2->t[1];
	result.t[2] = t1->t[2] * t2->t[2];
	result.t[3] = t1->t[3] * t2->t[3];
	return (result);
}
