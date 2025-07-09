# ifndef FT_MATRIX_H
# define FT_MATRIX_H

# define SIZE 4

# include "miniRt.h"

typedef struct s_mat
{
	float m[SIZE][SIZE];
} t_mat;

typedef struct s_mat3
{
	float m[SIZE -1][SIZE -1];
} t_mat3;

typedef struct s_mat2
{
	float m[SIZE -2][SIZE -2];
} t_mat2;

typedef struct s_ray
{
	t_tuple origin;
	t_tuple direction;
} t_ray;

void matrix(t_mat *m);
void matrix_print(t_mat *mt);
void matrix_multiply(t_mat *m0, t_mat *m1, t_mat *m2);
void indentity(t_mat *m0);
void matrix_transpose(t_mat *m0, t_mat *m1);

void	submatrix4x4(t_mat3 *m0, t_mat *m1, int column, int row);
void	submatrix3x3(t_mat2 *m0, t_mat3 *m1, int column, int row);
void	matrix_multiply_by_tuple(t_tuple *t0, t_mat *m0, t_tuple *t1);
float	det2x2(t_mat2 *m0);
float	minor(t_mat3 *m0, int column, int row);


float det3x3(t_mat3 *m);
float det4x4(t_mat *m);
bool matrix_inverse(t_mat *out, t_mat *in);
void transform(t_ray *rp, t_ray *r, t_mat *m);

void translation(t_mat *m0, float x, float y, float z);
void scalling(t_mat *m0, float x, float y, float z);
void rotate_x(t_mat *m0, float r);
void rotate_y(t_mat *m0, float r);
void rotate_z(t_mat *m0, float r);
# endif
