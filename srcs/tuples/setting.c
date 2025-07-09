/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 20:37:05 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/08 20:41:24 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Initializes a tuple as a point with the given (x, y, z) coordinates.
 * The w-component is set to 1.0 to indicate a point.
 */
void	point(t_tuple *p, float x, float y, float z)
{
	p->t[0] = x;
	p->t[1] = y;
	p->t[2] = z;
	p->t[3] = 1.0;
}

/**
 * Initializes a tuple as a color with the given (r, g, b) values.
 * The w-component is set to 1.0 for consistency, though it may not be used.
 */
void	color(t_tuple *p, float x, float y, float z)
{
	p->t[0] = x;
	p->t[1] = y;
	p->t[2] = z;
	p->t[3] = 1.0;
}

/**
 * Initializes a tuple as a vector with the given (x, y, z) components.
 * The w-component is set to 0.0 to indicate a vector.
 */
void	vector(t_tuple *p, float x, float y, float z)
{
	p->t[0] = x;
	p->t[1] = y;
	p->t[2] = z;
	p->t[3] = 0.0;
}

/**
 * Prints the components of a tuple (x, y, z, w) in a formatted manner.
 * Useful for debugging and inspecting tuple values.
 */
void	tuple_print(t_tuple *tp)
{
	printf(" | x : %8.5f", tp->t[0]);
	printf(" | y : %8.5f", tp->t[1]);
	printf(" | z : %8.5f", tp->t[2]);
	printf(" | w : %8.5f\n", tp->t[3]);
}
