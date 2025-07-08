# ifndef FT_MATRIX_H
# define FT_MATRIX_H

# define SIZE 4

# include "miniRt.h"

typedef struct s_mat
{
	float m[SIZE][SIZE];
} t_mat;

void matrix(t_mat *m);
void matrix_print(t_mat *mt);
void matrix_multiply(t_mat *m0, t_mat *m1, t_mat *m2);
# endif
