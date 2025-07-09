# ifndef FT_GRAPHICS_H
# define FT_GRAPHICS_H

# include "miniRt.h"

typedef struct s_ray
{
	t_tuple *origin;
	t_tuple *direction;
} t_ray;

typedef struct s_material
{
	float ambient;
	float diffiuse;
	float specular;
	float shininess;
	t_tuple *color;
} t_material;

typedef struct s_object
{
	float x;
	float y;
	float z;
	float id;
	float type;
	float radius;
	t_mat *transform;
	t_material *material;
} t_object;

typedef struct s_intersect
{
	float value;
	t_object *object;
} t_intersect;

typedef struct s_intersect
{
	float value;
	t_object *object;
} t_intersect;

typedef struct s_intersections
{
	int count;
	t_intersect *intersect;
	struct s_intersections *next;
} t_intersections;

void position(t_tuple *pp, t_ray *r, float t);

# endif
