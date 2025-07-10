# ifndef FT_GRAPHICS_H
# define FT_GRAPHICS_H

# include "miniRt.h"

typedef struct s_material
{
	float ambient;
	float diffiuse;
	float specular;
	float shininess;
	t_tuple color;
} t_material;

typedef struct s_light
{
	t_tuple color;
	t_tuple position;
} t_light;

typedef struct s_object
{
	float x;
	float y;
	float z;
	float id;
	float type;
	float radius;
	t_mat transform;
	t_mat invs;
	t_material *material;
} t_object;

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
t_intersect *intersection(double t, t_object *object);
t_intersect *cal_intersects(t_object *object, t_ray *rp, t_intersect out[2]);
t_intersections *intersections(t_intersections *xs, t_intersect *intersect);
t_intersect *hit(t_intersections *xs);

t_intersections *intersections_sort(t_intersections *xs);
void free_intersections(t_intersections *xs);
void set_transform(t_mat *m1, t_mat *m2);
uint32_t tuple_to_color(t_tuple *tp);

void normal_at(t_tuple *normal, t_object *s, t_tuple *world_point);
void reflect(t_tuple *out, t_tuple *in, t_tuple *normal);
void point_light(t_light *light, t_tuple *position, t_tuple *intensity);
void lighting(t_tuple *out, t_material *m, t_light *light, t_tuple *position, t_tuple *eye, t_tuple *normal);

# endif
