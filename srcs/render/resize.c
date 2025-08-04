/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 23:00:00 by aoshinth          #+#    #+#             */
/*   Updated: 2025/08/04 06:08:42 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

char	*type_name(int type)
{
	char	*type_name;

	if (type == SPHERE)
		type_name = "sphere";
	if (type == CYLINDER)
		type_name = "cylinder";
	if (type == PLANE)
		type_name = "plane";
	return (type_name);
}

void	select_next_object(t_state *state)
{
	static int	index = -1;
	t_object	*cur;
	int			i;

	i = 0;
	if (!state->world.components)
	{
		printf(" ⚠️  No objects in scene.\n");
		return ;
	}
	index = (index + 1) % state->world.obj_count;
	cur = state->world.components;
	while (cur && i++ < index)
		cur = cur->next;
	state->selected_object = cur;
	if (cur)
	{
		printf("🔄 Selected [%d]: object=%s radius=%.2f height=%.2f\n",
			index, type_name(cur->type), cur->radius, cur->height);
	}
	state->interact = OBJECT;
}
