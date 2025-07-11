# include "include/miniRt.h"

# define WIDTH  1000
# define HEIGHT  800

float get_value(t_intersect *xs)
{
	float value = 0.0;
	if(xs)
	{
		if(xs[0].value > 0)
			value = xs[0].value;
		if(xs[1].value > 0)
		{
			if(xs[0].value > xs[1].value)
				value = xs[1].value;
		}
	}
	return value;
}

int main(void)
{
	t_world world;

	t_object *s1, *s2;

	s1 = ft_calloc(1, sizeof(t_object));
	s2 = ft_calloc(1, sizeof(t_object));

	t_material mat1, mat2;

	mat1.ambient = 0.1f;
	mat1.diffuse = 0.7f;
	mat1.specular = 0.2f;
	mat1.shininess = 200.0f;
	color(&mat1.color, 0.8f, 1.0f, 0.6f);

	mat2.ambient = 0.1f;
	mat2.diffuse = 0.9f;
	mat2.specular = 0.9f;
	mat2.shininess = 200.0f;
	color(&mat2.color, 1.0f, 1.0f, 1.0f);

	s1->id = 1;
	s1->type = 1;
	s1->x = 0.0f;
	s1->y = 0.0f;
	s1->z = 0.0f;
	s1->radius = 1.0f;
	s1->material = &mat1;
	identity(&s1->transform);
	matrix_inverse(&s1->invs, &s1->transform);
	s1->next = s2;

	t_mat m1;
	scaling(&m1, 0.5f, 0.5f, 0.5f);
	s2->id = 2;
	s2->type = 1;
	s2->x = 0.0f;
	s2->y = 0.0f;
	s2->z = 0.0f;
	s2->radius = 1.0f;
	s2->material = &mat2;
	set_transform(&s2->transform, &m1);
	matrix_inverse(&s2->invs, &s2->transform);
	s2->next = NULL;

	point(&world.light.position, -10.0f, 10.0f, -10.0f);
	color(&world.light.color, 1.0f, 1.0f, 1.0f);
	world.components = s1;

	t_ray r;
	point(&r.origin, 0.0f, 0.0f, -5.0f);
	vector(&r.direction, 0.0f, 0.0f, 1.0f);

	t_intersect *xxs, *node;
	xxs = intersect_world(&world, &r);
	xxs = intersections_sort(xxs);
	int i = 1;
	if(xxs)
	{
		node = xxs;
		while(node)
		{
			printf("node[%d].value : %.2f\n", i, node->value);
			node = node->next;
			i++;
		}
	}
	free(s1);
	free(s2);
	free_intersections(xxs);
	return 0;
}
