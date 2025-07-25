#include "include/miniRt.h"

void camera_init(t_camera *camera, int hsize, int vsize, float fov)
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

void default_state(t_state *state)
{
	state->world.ambient = 0.0f;
	state->world.diffuse = 0.0f;
	state->world.set_ambient = false;
	state->world.set_light = false;

	color(&state->world.colour, 1.0f, 1.0f, 1.0f);
	point(&state->world.light.position, 0.0f, 0.0f, 0.0f);
	color(&state->world.light.color, 1.0f, 1.0f, 1.0f);

	camera_init(&state->camera, WIDTH, HEIGHT, M_PI / 3.0f);
	state->camera.set_camera = false;
}

void print_object(t_object *s)
{
	if (!s)
		return;

	printf("id : %d\n", s->id);
	printf("type : %d\n", s->type);
	printf("s.ambient : %.3f\n", s->ambient);
	printf("s.diffuse : %.3f\n", s->diffuse);
	printf("s.specular : %.3f\n", s->specular);
	printf("s.shininess : %.3f\n", s->shininess);
	printf("s.x : %.3f\n", s->x);
	printf("s.y : %.3f\n", s->y);
	printf("s.z : %.3f\n", s->z);
	printf("s.radius : %.3f\n", s->radius);
	printf("s.color :\n");
	tuple_print(&s->color);
	printf("s.transform :\n");
	matrix_print(&s->transform);
}

void print_things(t_state *state)
{
	printf("state.world.ambient : %.3f\n", state->world.ambient);
	printf("state.world.colour :\n");
	tuple_print(&state->world.colour);
	printf("state.world.diffuse : %.3f\n", state->world.diffuse);
	printf("state.world.light.color :\n");
	tuple_print(&state->world.light.color);
	printf("state.world.light.position :\n");
	tuple_print(&state->world.light.position);

	printf("state.camera.hsize : %d\n", state->camera.hsize);
	printf("state.camera.vsize : %d\n", state->camera.vsize);
	printf("state.camera.half_height : %.3f\n", state->camera.half_height);
	printf("state.camera.half_width : %.3f\n", state->camera.half_width);
	printf("state.camera.pixel_size : %.3f\n", state->camera.pixel_size);
	printf("state.camera.fov : %.3f\n", state->camera.fov);

	printf("state.camera.transform :\n");
	matrix_print(&state->camera.transform);
	printf("state.camera.invs :\n");
	matrix_print(&state->camera.invs);

	printf("object list :\n");
	t_object *s = state->world.components;
	while (s)
	{
		print_object(s);
		s = s->next;
	}
}

int main(int argc, char *argv[])
{
	t_state	*state = ft_calloc(1, sizeof(t_state));
	if (!state)
		return (1);

	t_mat m = scaling(-1.0f, 1.0f, -1.0f);
	printf("scaling matrix:\n");
	matrix_print(&m);

	default_state(state);

	if (argc == 2)
	{
		if (init_file_reader(argv[1], state))
			render_image(state);
	}
	else
		ft_error("[ incorrect arguments! ]\n");

	clean_up(state);
	free(state);
	return (0);
}
