/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 05:30:25 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/01 05:48:26 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

int	move_light(mlx_key_data_t key, t_state *state)
{
	t_light	*light;
	float	step ;

	light = &state->world.light;
	if(!state->world.set_light)
	{
		printf(" 💡 No light source in the scene.\n");
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
	return (SUCCESS);
}
