# include "../../include/miniRt.h"

void matrix_multiply_by_tuple(t_tuple *t0, t_mat *m0, t_tuple *t1)
{
	int i;
	int j;

	i = 0;
	while (i < SIZE)
	{
		j = 0;
		while(j < SIZE)
		{
			t0->t[i] += (m0->m[i][j] * t1->t[j]);
			j++;
		}
		i++;
	}
}

float det2x2(t_mat2 *m0)
{
	float result;

	result = 0.0;
	result = m0->m[0][0] * m0->m[1][1] -  m0->m[0][1] * m0->m[1][0];
	return result;
}

void submatrix4x4(t_mat3 *m0, t_mat *m1, int column, int row)
{
	int i;
	int j;
	int si;
	int sj;

	i = 0;
	si = 0;
	while(i < SIZE)
	{
		if(i == column)
		{
			i++;
			continue;
		}
		j = 0;
		sj = 0;
		while(j < SIZE)
		{
			if(j != row)
				m0->m[si][sj++] = m1->m[i][j];
			j++;
		}
		si++;
		i++;
	}
}

void submatrix3x3(t_mat2 *m0, t_mat3 *m1, int column, int row)
{
	int i;
	int j;
	int si;
	int sj;

	i = 0;
	si = 0;
	while(i < SIZE - 1)
	{
		if(i == column)
		{
			i++;
			continue;
		}
		j = 0;
		sj = 0;
		while(j < SIZE -1)
		{
			if(j != row)
				m0->m[si][sj++] = m1->m[i][j];
			j++;
		}
		si++;
		i++;
	}
}

float minor(t_mat3 *m0, int column, int row)
{
	float result;

	result = 0.0;
	t_mat2 m2;
	submatrix3x3(&m2, m0, column, row);
	result = det2x2(&m2);
	return result;
}
