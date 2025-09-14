/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:42:29 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/04 06:17:51 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/miniRt.h"

/**
 * Initializes camera with size and fov, and resets transforms.
 * Computes half sizes and pixel_size; fov is in radians.
*/
void	camera_init(t_camera *camera, int hsize, int vsize, float fov)
{
	float	half_view;
	float	aspect;

	camera->hsize = hsize;
	camera->vsize = vsize;
	camera->fov = fov;
	camera->transform = identity();
	camera->invs = identity();
	half_view = tanf(fov / 2.0f);
	aspect = hsize / (float)vsize;
	if (aspect >= 1.0f)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	camera->pixel_size = (camera->half_width * 2.0f) / camera->hsize;
}

/**
 * Sets default world, camera, and interaction state.
 * Clears object list, zeroes lights, sets colors to white.
 * Resets flags and selection to defaults.
*/
void	default_state(t_state *state)
{
	state->world.ambient = 0.0f;
	state->world.diffuse = 0.0f;
	state->world.set_ambient = false;
	state->world.set_light = false;
	state->world.obj_count = 0;
	state->world.components = NULL;
	color(&state->world.colour, 1.0f, 1.0f, 1.0f);
	point(&state->world.light.position, 0.0f, 0.0f, 0.0f);
	color(&state->world.light.color, 1.0f, 1.0f, 1.0f);
	camera_init(&state->camera, WIDTH, HEIGHT, M_PI / 3.0f);
	state->camera.set_camera = false;
	state->done = false;
	state->interact = DEFAULT;
	state->mode = DEFAULT;
	state->selected_object = NULL;
}

/**
 * Allocates state, applies defaults, and parses args.
 * On a valid .rt file, shows help and renders the scene.
 * On bad args, prints an error; always cleans up.
*/
int	main(int argc, char *argv[])
{
	t_state	*state;

	state = ft_calloc(1, sizeof(t_state));
	if (!state)
		return (1);
	default_state(state);
	if (argc == 2)
	{
		if (init_file_reader(argv[1], state))
		{
			help_menu();
			render_image(state);
		}
	}
	else
		ft_error("[ incorrect arguments! ]\n");
	clean_up(state);
	free(state);
	return (0);
}
