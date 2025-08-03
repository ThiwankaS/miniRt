/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 08:43:58 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/02 16:04:59 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

void	light_interact_mode(mlx_key_data_t keydata, t_state *state)
{
	if (interact_light(keydata, state) == SUCCESS)
	{
		render(state);
		printf("✅ update object !\n");
	}
	if (keydata.key == MLX_KEY_H && state->interact == LIGHT)
		help_light();
}

void	sphere_interaction(mlx_key_data_t key, t_state *state)
{
	t_object	*selected;

	selected = state->selected_object;
	if (state->mode == DEFAULT || !selected)
		return ;
	if (state->mode == RESIZE && resize_sphere(key, selected) == SUCCESS)
	{
		render(state);
		printf("✅ update object !\n");
	}
	if (state->mode == MOVE && move_sphere(key, selected) == SUCCESS)
	{
		render(state);
		printf("✅ update object !\n");
	}
}

void	spehere_interact_mode(mlx_key_data_t keydata, t_state *state)
{
	bool	left;
	bool	right;

	if (state->interact == DEFAULT)
		return ;
	left = mlx_is_key_down(state->mlx, MLX_KEY_LEFT_CONTROL);
	right = mlx_is_key_down(state->mlx, MLX_KEY_RIGHT_CONTROL);
	if (keydata.key == MLX_KEY_M && (left || right))
	{
		state->mode = MOVE;
		printf("you can move the selected sphere\n");
	}
	else if (keydata.key == MLX_KEY_R && (left || right))
	{
		state->mode = RESIZE;
		printf("you can resize the selected sphere\n");
	}
	else if (keydata.key == MLX_KEY_H)
		help_sphere();
	sphere_interaction(keydata, state);
}

void	select_mode(mlx_key_data_t keydata, t_state *state)
{
	t_object	*selected;

	(void)keydata;
	selected = state->selected_object;
	if (state->interact == LIGHT)
		light_interact_mode(keydata, state);
	if (state->interact == CAMERA)
		printf(" 📹 mode selection for camera\n");
	if (state->interact == OBJECT && selected)
	{
		if (selected->type == SPHERE)
			spehere_interact_mode(keydata, state);
		if (selected->type == CYLINDER)
			cylinder_interact_mode(keydata, state);
		if (selected->type == PLANE)
			printf("mode selection for plane\n");
	}
}
