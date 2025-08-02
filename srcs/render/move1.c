/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 05:30:25 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/02 15:54:25 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

int	interact_light(mlx_key_data_t key, t_state *state)
{
	t_light	*light;
	float	step ;

	light = &state->world.light;
	if (!state->world.set_light)
	{
		printf(" ⛔ No light source in the scene.\n");
		return (FAILURE);
	}
	step = 1.0f;
	if (key.key == MLX_KEY_W)
		light->position.t[1] += step;
	else if (key.key == MLX_KEY_S)
		light->position.t[1] -= step;
	else if (key.key == MLX_KEY_A)
		light->position.t[0] -= step;
	else if (key.key == MLX_KEY_D)
		light->position.t[0] += step;
	else if (key.key == MLX_KEY_Z)
		light->position.t[2] += step;
	else if (key.key == MLX_KEY_X)
		light->position.t[2] -= step;
	else
		return (FAILURE);
	return (SUCCESS);
}

int	interact_object(mlx_key_data_t key, t_state *state)
{
	t_object	*selected;

	selected = state->selected_object;
	if (state->interact != OBJECT || !selected)
		return (FAILURE);
	else if (selected->type == SPHERE)
		return (resize_sphere(key, selected));
	else if (selected->type == CYLINDER)
		return (resize_cylinder(key, selected));
	return (FAILURE);
}

void	select_ligth_source(t_state *state)
{
	state->interact = LIGHT;
	printf("💡 Interactive mood for light ON.\n");
}

void	select_exit_interaction(t_state *state)
{
	state->interact = DEFAULT;
	state->selected_object = NULL;
	state->mode = DEFAULT;
	printf("👋 Interactive mood OFF.\n");
}

void	select_camera(t_state *state)
{
	state->interact = CAMERA;
	printf("📸 Interactive mood for camera ON.\n");
}
