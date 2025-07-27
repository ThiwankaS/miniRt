# ifndef FT_TUPLE_H
# define FT_TUPLE_H

# include "miniRt.h"

typedef struct s_tuple
{
	float t[4];
} t_tuple;

/**
 * debugging helper functions
*/
void tuple_print(t_tuple *tp);

/**
 * creating some useful derevative custome data types base on primary data structure
 */
void point(t_tuple *p, float x, float y, float z);
void color(t_tuple *p, float x, float y, float z);
void vector(t_tuple *p, float x, float y, float z);

/**
 * arithmatic operations on tuples
 */
t_tuple tuple_add(t_tuple *t1, t_tuple *t2);
t_tuple tuple_subtract(t_tuple *t1, t_tuple *t2);
t_tuple tuple_negate(t_tuple *t2);
t_tuple tuple_multiply_scalar(t_tuple *t1, float a);
t_tuple tuple_divide_scalar(t_tuple *t1, float a);

float dot(t_tuple *t1, t_tuple *t2);
float tuple_magnitute(t_tuple *t0);
t_tuple normalize(t_tuple *t1);
t_tuple cross(t_tuple *t1, t_tuple *t2);
t_tuple schur_product(t_tuple *t1, t_tuple *t2);

# endif
