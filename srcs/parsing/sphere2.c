/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 13:53:50 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/29 20:49:32 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

void	creating_sphere_object(t_object *s)
{
	t_mat	m1;
	t_mat	m2;

	m1 = scaling(s->radius, s->radius, s->radius);
	m2 = translation(s->x, s->y, s->z);
	s->transform = matrix_multiply(&m2, &m1);
	matrix_inverse(&s->invs, &s->transform);
	s->invs_trans = matrix_transpose(&s->invs);
}
