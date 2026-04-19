#include "../../include/miniRt.h"

t_mat	matrix(void)
{
	t_mat	m;
	int		row;
	int		col;

	for (col = 0; col < SIZE; col++)
		for (row = 0; row < SIZE; row++)
			m.m[col][row] = 0.0f;
	return (m);
}

void	matrix_print(t_mat *mt)
{
	int	row;
	int	col;

	for (col = 0; col < SIZE; col++)
	{
		for (row = 0; row < SIZE; row++)
			printf(" | m[%d][%d] : %6.3f", col, row, mt->m[col][row]);
		printf("\n");
	}
}

t_mat	matrix_multiply(t_mat *m1, t_mat *m2)
{
	t_mat	result;
	int		row;
	int		col;

	for (col = 0; col < SIZE; col++)
	{
		for (row = 0; row < SIZE; row++)
		{
			result.m[col][row]
				= m1->m[col][0] * m2->m[0][row]
				+ m1->m[col][1] * m2->m[1][row]
				+ m1->m[col][2] * m2->m[2][row]
				+ m1->m[col][3] * m2->m[3][row];
		}
	}
	return (result);
}

t_mat	identity(void)
{
	t_mat	m;

	m = matrix();
	m.m[0][0] = 1.0f;
	m.m[1][1] = 1.0f;
	m.m[2][2] = 1.0f;
	m.m[3][3] = 1.0f;
	return (m);
}

t_mat	matrix_transpose(t_mat *m1)
{
	t_mat	result;
	int		row;
	int		col;

	for (col = 0; col < SIZE; col++)
		for (row = 0; row < SIZE; row++)
			result.m[col][row] = m1->m[row][col];
	return (result);
}

t_tuple	matrix_multiply_by_tuple(t_mat *m0, t_tuple *t1)
{
	t_tuple	result;

	result.t[0] = m0->m[0][0] * t1->t[0] + m0->m[0][1] * t1->t[1]
		+ m0->m[0][2] * t1->t[2] + m0->m[0][3] * t1->t[3];
	result.t[1] = m0->m[1][0] * t1->t[0] + m0->m[1][1] * t1->t[1]
		+ m0->m[1][2] * t1->t[2] + m0->m[1][3] * t1->t[3];
	result.t[2] = m0->m[2][0] * t1->t[0] + m0->m[2][1] * t1->t[1]
		+ m0->m[2][2] * t1->t[2] + m0->m[2][3] * t1->t[3];
	result.t[3] = m0->m[3][0] * t1->t[0] + m0->m[3][1] * t1->t[1]
		+ m0->m[3][2] * t1->t[2] + m0->m[3][3] * t1->t[3];
	return (result);
}

float	det2x2(t_mat2 *m0)
{
	return (m0->m[0][0] * m0->m[1][1] - m0->m[0][1] * m0->m[1][0]);
}

t_mat3	submatrix4x4(t_mat *m1, int remove_row, int remove_col)
{
	t_mat3	m0;
	int		i;
	int		j;
	int		si;
	int		sj;

	si = 0;
	for (i = 0; i < SIZE; i++)
	{
		if (i == remove_row)
			continue ;
		sj = 0;
		for (j = 0; j < SIZE; j++)
		{
			if (j == remove_col)
				continue ;
			m0.m[si][sj++] = m1->m[i][j];
		}
		si++;
	}
	return (m0);
}

t_mat2	submatrix3x3(t_mat3 *m1, int remove_row, int remove_col)
{
	t_mat2	m0;
	int		i;
	int		j;
	int		si;
	int		sj;

	si = 0;
	for (i = 0; i < (SIZE - 1); i++)
	{
		if (i == remove_row)
			continue ;
		sj = 0;
		for (j = 0; j < (SIZE - 1); j++)
		{
			if (j == remove_col)
				continue ;
			m0.m[si][sj++] = m1->m[i][j];
		}
		si++;
	}
	return (m0);
}

float	minor(t_mat3 *m0, int remove_row, int remove_col)
{
	t_mat2	m2;

	m2 = submatrix3x3(m0, remove_row, remove_col);
	return (det2x2(&m2));
}

static float	matrix_cofactor_3x3(t_mat3 *m0, int row, int column)
{
	float	det;

	det = minor(m0, row, column);
	if ((row + column) % 2 != 0)
		det = det * -1;
	return (det);
}

float	det3x3(t_mat3 *m)
{
	float	det;

	det = 0.0;
	det += m->m[0][0] * matrix_cofactor_3x3(m, 0, 0);
	det += m->m[0][1] * matrix_cofactor_3x3(m, 0, 1);
	det += m->m[0][2] * matrix_cofactor_3x3(m, 0, 2);
	return (det);
}

float	det4x4(t_mat *m)
{
	int		j;
	float	det;
	float	cofactor;
	t_mat3	sub;

	det = 0.0;
	for (j = 0; j < SIZE; j++)
	{
		sub = submatrix4x4(m, 0, j);
		cofactor = det3x3(&sub);
		if (j % 2 != 0)
			cofactor = -cofactor;
		det += m->m[0][j] * cofactor;
	}
	return (det);
}

bool	matrix_inverse(t_mat *out, t_mat *in)
{
	int		row;
	int		col;
	float	det;
	float	cofactor;
	t_mat3	sub;

	det = det4x4(in);
	if (det == 0.0)
		return (false);
	for (row = 0; row < SIZE; row++)
	{
		for (col = 0; col < SIZE; col++)
		{
			sub = submatrix4x4(in, row, col);
			cofactor = det3x3(&sub);
			if ((row + col) % 2 != 0)
				cofactor = -cofactor;
			out->m[col][row] = cofactor / det;
		}
	}
	return (true);
}

t_ray	transform(t_ray *r, t_mat *m)
{
	t_ray	rp;

	rp.origin = matrix_multiply_by_tuple(m, &r->origin);
	rp.direction = matrix_multiply_by_tuple(m, &r->direction);
	rp.direction = normalize(&rp.direction);
	rp.direction.t[3] = 0.0f;
	return (rp);
}

t_mat	translation(float x, float y, float z)
{
	t_mat	m;

	m = identity();
	m.m[0][3] = x;
	m.m[1][3] = y;
	m.m[2][3] = z;
	return (m);
}

t_mat	scaling(float x, float y, float z)
{
	t_mat	m;

	m = identity();
	m.m[0][0] = x;
	m.m[1][1] = y;
	m.m[2][2] = z;
	return (m);
}

t_mat	rotate_x(float r)
{
	t_mat	m;
	float	c;
	float	s;

	m = identity();
	c = cosf(r);
	s = sinf(r);
	m.m[1][1] = c;
	m.m[1][2] = -s;
	m.m[2][1] = s;
	m.m[2][2] = c;
	return (m);
}

t_mat	rotate_y(float r)
{
	t_mat	m;
	float	c;
	float	s;

	m = identity();
	c = cosf(r);
	s = sinf(r);
	m.m[0][0] = c;
	m.m[0][2] = s;
	m.m[2][0] = -s;
	m.m[2][2] = c;
	return (m);
}

t_mat	rotate_z(float r)
{
	t_mat	m;
	float	c;
	float	s;

	m = identity();
	c = cosf(r);
	s = sinf(r);
	m.m[0][0] = c;
	m.m[0][1] = -s;
	m.m[1][0] = s;
	m.m[1][1] = c;
	return (m);
}

t_mat	rotate_axis(t_tuple *axis, float angle)
{
	float	c;
	float	s;
	float	t;
	t_mat	rotate;

	c = cosf(angle);
	s = sinf(angle);
	t = 1.0f - c;
	rotate = identity();
	rotate.m[0][0] = t * axis->t[0] * axis->t[0] + c;
	rotate.m[0][1] = t * axis->t[0] * axis->t[1] - s * axis->t[2];
	rotate.m[0][2] = t * axis->t[0] * axis->t[2] + s * axis->t[1];
	rotate.m[1][0] = t * axis->t[0] * axis->t[1] + s * axis->t[2];
	rotate.m[1][1] = t * axis->t[1] * axis->t[1] + c;
	rotate.m[1][2] = t * axis->t[1] * axis->t[2] - s * axis->t[0];
	rotate.m[2][0] = t * axis->t[0] * axis->t[2] - s * axis->t[1];
	rotate.m[2][1] = t * axis->t[1] * axis->t[2] + s * axis->t[0];
	rotate.m[2][2] = t * axis->t[2] * axis->t[2] + c;
	return (rotate);
}
