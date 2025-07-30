/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 23:00:00 by aoshinth          #+#    #+#             */
/*   Updated: 2025/07/30 13:44:17 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

int	count_objects(t_state *state)
{
	t_object	*cur;
	int			count;

	count = 0;
	cur = state->world.components;
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	state->world.obj_count = count;
	return (count);
}

void	select_next_object(t_state *state)
{
	static int	index = -1;
	t_object	*cur;
	int			i;

	i = 0;
	if (!state->world.components)
	{
		printf("⚠️ No objects in scene.\n");
		return ;
	}
	if (state->world.obj_count == 0)
		count_objects(state);
	index = (index + 1) % state->world.obj_count;
	cur = state->world.components;
	while (cur && i++ < index)
		cur = cur->next;
	state->selected_object = cur;
	if (cur)
		printf("🔄 Selected [%d]: type=%d radius=%.2f height=%.2f\n",
			index, cur->type, cur->radius, cur->height);
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

int	resize_object(mlx_key_data_t key, t_object *obj)
{
	if (!obj)
		return (FAILURE);
	if (obj->type == SPHERE || obj->type == CYLINDER)
	{
		if (key.key == MLX_KEY_UP)
		{
			obj->radius += 0.1f;
		}
		else if (key.key == MLX_KEY_DOWN)
			obj->radius = fmaxf(0.1f, obj->radius - 0.1f);
	}
	if (obj->type == CYLINDER)
	{
		if (key.key == MLX_KEY_RIGHT)
			obj->height += 0.1f;
		else if (key.key == MLX_KEY_LEFT)
			obj->height = fmaxf(0.1f, obj->height - 0.1f);
	}
	return (SUCCESS);
}

int	change_value(mlx_key_data_t keydata, t_object *selected)
{
	if (!selected)
		return (FAILURE);
	if (selected->type == SPHERE || selected->type == CYLINDER)
		return (resize_object(keydata, selected));
	return (FAILURE);
}
