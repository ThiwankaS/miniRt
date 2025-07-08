# ifndef FT_TUPLE_H
# define FT_TUPLE_H

# include "miniRt.h"

typedef struct s_tuple
{
	float t[4];
} t_tuple;

void point(t_tuple *p, float x, float y, float z);
void color(t_tuple *p, float x, float y, float z);
void vector(t_tuple *p, float x, float y, float z);

# endif
