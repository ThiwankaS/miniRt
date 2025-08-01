/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 23:00:00 by aoshinth          #+#    #+#             */
/*   Updated: 2025/08/01 05:00:49 by tsomacha         ###   ########.fr       */
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
}

void	handle_resize(t_state *state, int32_t cur_w, int32_t cur_h)
{
	state->camera.hsize = cur_w;
	state->camera.vsize = cur_h;
	update_fov(&state->camera, state->camera.fov);
	if (state->img)
		mlx_delete_image(state->mlx, state->img);
	state->img = mlx_new_image(state->mlx, cur_w, cur_h);
	mlx_image_to_window(state->mlx, state->img, 0, 0);
	render(state);
}

int	change_value(mlx_key_data_t keydata, t_state *state)
{
	t_object *selected;

	selected = state->selected_object;
	if (state->interactive == true)
		return (move_light(keydata, state));
	else if (!selected)
		return (FAILURE);
	else if (selected->type == SPHERE)
		return (resize_sphere(keydata, selected));
	else if (selected->type == CYLINDER)
		return (resize_cylinder(keydata, selected));
	return (FAILURE);
}
