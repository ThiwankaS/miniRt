#include "include/miniRt.h"

void camera_init(t_camera *camera, int hsize, int vsize, float fov)
{
	float	half_view;
	float	aspect;

	camera->hsize = hsize;
	camera->vsize = vsize;
	camera->fov = fov;
	identity(&camera->transform);
	identity(&camera->invs);
	half_view = tan(fov/2);
	aspect = hsize /(float) vsize;
	if(aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	camera->pixel_size = (camera->half_width * 2) / camera->hsize;
}


void default_state(t_state *state)
{
	state->world.ambient = 0.0f;
	state->world.diffuse = 0.0f;
	state->world.set_ambient = false;
	state->world.set_light = false;
	color(&state->world.colour, 1.0f, 1.0f, 1.0f);
	point(&state->world.light.position, 0.0f, 0.0f, 0.0f);
	color(&state->world.light.color, 1.0f, 1.0f, 1.0f);
	camera_init(&state->camera, WIDTH, HEIGHT, M_PI / 3);
	state->camera.set_camera = false;
}

void print_things(t_state *state)
{
	printf("state.world.ambient : %.3f\n", state->world.ambient);
	printf("state->world.colour : \n");
	tuple_print(&state->world.colour);
	printf("state.world.diffuse : %.3f\n", state->world.diffuse);
	printf("state->world.light.color : \n");
	tuple_print(&state->world.light.color);
	printf("state->world.light.position : \n");
	tuple_print(&state->world.light.position);
	printf("state.camera.hszie : %d\n", state->camera.hsize);
	printf("state.camera.vszie : %d\n", state->camera.vsize);
	printf("state.camera.half_height : %.3f\n", state->camera.half_height);
	printf("state.camera.half_width : %.3f\n", state->camera.half_width);
	printf("state.camera.pixel_size : %.3f\n", state->camera.pixel_size);
	printf("state.camera.fov : %.3f\n", state->camera.fov);
	printf("state->camera.transform : \n");
	matrix_print(&state->camera.transform);
	printf("state->camera.invs : \n");
	matrix_print(&state->camera.invs);
}

int	main(int argc, char *argv[])
{
	t_state	state;

	default_state(&state);
	if(argc != 1)
	{
		init_file_reader(argv[1], &state);
	}
	else
		ft_error("[ incorrect arguments ! ] \n");
	print_things(&state);
	return (0);
}
