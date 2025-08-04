/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 05:16:41 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/04 05:25:29 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

void	handle_window_resize(t_state *state, int32_t cur_w, int32_t cur_h)
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
