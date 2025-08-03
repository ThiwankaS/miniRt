/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 08:43:51 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/03 06:17:29 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"


int	resize_cylinder(mlx_key_data_t key, t_object *obj)
{
	if (!obj)
		return (FAILURE);
	if (key.key == MLX_KEY_UP)
		obj->radius += 0.1f;
	else if (key.key == MLX_KEY_DOWN)
		obj->radius = fmaxf(0.5f, obj->radius - 0.1f);
	else if (key.key == MLX_KEY_RIGHT)
		obj->height += 0.1f;
	else if (key.key == MLX_KEY_LEFT)
		obj->height = fmaxf(0.5f, obj->height - 0.1f);
	else
		return (FAILURE);
	return (SUCCESS);
}

int	move_cylinder(mlx_key_data_t key, t_object *obj)
{
	float	step;

	step = 0.1f;
	if (key.key == MLX_KEY_W)
		obj->y += step;
	else if (key.key == MLX_KEY_S)
		obj->y -= step;
	else if (key.key == MLX_KEY_A)
		obj->x -= step;
	else if (key.key == MLX_KEY_D)
		obj->x += step;
	else if (key.key == MLX_KEY_Z)
		obj->z += step;
	else if (key.key == MLX_KEY_X)
		obj->z -= step;
	else
		return (FAILURE);
	creating_cylinder_object(obj);
	return (SUCCESS);
}

void	cylinder_interaction(mlx_key_data_t key, t_state *state)
{
	t_object	*selected;

	selected = state->selected_object;
	if (state->mode == DEFAULT || !selected)
		return ;
	if (state->mode == RESIZE && resize_cylinder(key, selected) == SUCCESS)
	{
		render(state);
		printf("✅ update object !\n");
	}
	if (state->mode == MOVE && move_cylinder(key, selected) == SUCCESS)
	{
		render(state);
		printf("✅ update object !\n");
	}
	if (state->mode == ROTATE && move_sphere(key, selected) == SUCCESS)
	{
		printf("rotating\n");
		printf("✅ update object !\n");
	}
}

void	cylinder_interact_mode(mlx_key_data_t keydata, t_state *state)
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
		printf("you can move the selected cylinder\n");
	}
	else if (keydata.key == MLX_KEY_R && (left || right))
	{
		state->mode = RESIZE;
		printf("you can resize the selected cylinder\n");
	}
	else if (keydata.key == MLX_KEY_S && (left || right))
	{
		state->mode = ROTATE;
		printf("you can resize the selected cylinder\n");
	}
	else if (keydata.key == MLX_KEY_H)
		help_mode();
	cylinder_interaction(keydata, state);
}
