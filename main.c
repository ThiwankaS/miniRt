#include "include/miniRt.h"

#define WIDTH 1600
#define HEIGHT 1200

void default_world(t_world *world)
{
	world->ambient = 0.0f;
	world->diffuse = 0.0f;
	world->set_ambient = false;
	world->set_light = false;
	color(&world->colour, 1.0f, 1.0f, 1.0f);
	point(&world->light.position, 0.0f, 0.0f, 0.0f);
	color(&world->light.color, 1.0f, 1.0f, 1.0f);
	world->components = NULL;
}

int	main(int argc, char *argv[])
{
	t_world	world;

	default_world(&world);
	if(argc != 1)
	{
		init_file_reader(argv[1], &world);
	}
	else
		ft_error("[ incorrect arguments ! ] \n");
	printf("world.ambient : %.2f\n", world.ambient);
	tuple_print(&world.colour);
	printf("world.diffuse : %.2f\n", world.diffuse);
	tuple_print(&world.light.color);
	tuple_print(&world.light.position);
	return (0);
}
