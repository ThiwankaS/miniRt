/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 04:37:43 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/30 08:52:31 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Updates the camera's view transform based on position and direction.
 * Builds an orientation matrix using the camera's forward and up vectors.
 */
void	update_view(t_camera *camera, t_tuple *p, t_tuple *d)
{
	t_tuple	from;
	t_tuple	forward;
	t_tuple	to;
	t_tuple	up;
	float	dot_product;

	point(&from, p->t[0], p->t[1], p->t[2]);
	vector(&forward, d->t[0], d->t[1], d->t[2]);
	vector(&up, 0.0f, 1.0f, 0.0f);
	dot_product = dot(&forward, &up);
	if (fabsf(dot_product) > 0.999f)
		vector(&up, 0.0f, 0.0f, 1.0f);
	up = normalize(&up);
	to = tuple_add(&from, &forward);
	view_trans(camera, &from, &to, &up);
}

/**
 * Adds a new object to the world's linked list of objects in the given state.
 * Appends to the end if the list is non-empty.
 */
void	add_object(t_state *state, t_object **s)
{
	t_object	*current;

	if (!state || !s || !*s)
		return ;
	if (!state->world.components)
		state->world.components = *s;
	else
	{
		current = state->world.components;
		while (current && current->next)
			current = current->next;
		current->next = *s;
	}
}

/**
 * Frees all objects in the world's linked list,
 * releasing allocated memory.
 */
void	clean_up(t_state *state)
{
	t_object	*current;
	t_object	*temp;

	current = state->world.components;
	while (current)
	{
		temp = current->next;
		free(current);
		current = temp;
	}
}

/**
 * Allocates and zero-initializes a new object structure.
 * Returns NULL on failure.
 */
t_object	*init_object(void)
{
	t_object	*s;

	s = ft_calloc(1, sizeof(t_object));
	if (!s)
		return (NULL);
	return (s);
}
