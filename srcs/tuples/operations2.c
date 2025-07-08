/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:28:36 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/08 20:33:39 by tsomacha         ###   ########.fr       */
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
	float	squared;

	x_squared = t0->t[0] * t0->t[0];
	y_squared = t0->t[1] * t0->t[1];
	z_squared = t0->t[2] * t0->t[2];
	w_squared = t0->t[3] * t0->t[3];
	squared = x_squared + y_squared + z_squared + w_squared;
	return (sqrtf(squared));
}

/**
 * Computes the dot product of two tuples (t1 and t2).
 * Returns the scalar result of: x1*x2 + y1*y2 + z1*z2 + w1*w2.
 */
float	dot(t_tuple *t1, t_tuple *t2)
{
	float	sum;

	sum = 0.0;
	sum += t1->t[0] * t2->t[0];
	sum += t1->t[1] * t2->t[1];
	sum += t1->t[2] * t2->t[2];
	sum += t1->t[3] * t2->t[3];
	return (sum);
}

/**
 * Normalizes the given tuple (t1) and stores the result in t0.
 * A normalized vector has magnitude 1 and points in the same direction.
 */
void	normalize(t_tuple *t0, t_tuple *t1)
{
	float	mag;

	mag = tuple_magnitute(t1);
	tuple_divide_scalor(t0, t1, mag);
}

/**
 * Computes the cross product of two vectors (t1 and t2) and
 * stores the result in t0.
 * Only the x, y, z components are used; w is set to 0.0.
 */
void	cross(t_tuple *t0, t_tuple *t1, t_tuple *t2)
{
	t0->t[0] = t1->t[1] * t2->t[2] - t1->t[2] * t2->t[1];
	t0->t[1] = t1->t[2] * t2->t[0] - t1->t[0] * t2->t[2];
	t0->t[2] = t1->t[0] * t2->t[1] - t1->t[1] * t2->t[0];
	t0->t[3] = 0.0;
}

/**
 * Performs the Schur (Hadamard) product — element-wise multiplication
 * of two tuples. Stores the result in t0.
 */
void	schur_product(t_tuple *t0, t_tuple *t1, t_tuple *t2)
{
	t0->t[0] = t1->t[0] * t2->t[0];
	t0->t[1] = t1->t[1] * t2->t[1];
	t0->t[2] = t1->t[2] * t2->t[2];
	t0->t[3] = t1->t[3] * t2->t[3];
}
