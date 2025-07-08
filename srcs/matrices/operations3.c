# include "../../include/miniRt.h"

float matrix_cofactor(t_mat3 *m0, int row, int column)
{
	float det;

	det = minor(m0, row, column);
	if((row + column) % 2 != 0)
		det = det * -1;
	return det;
}

float det3x3(t_mat3 *m)
{
	float det;

	det = 0.0;
	det += m->m[0][0] * matrix_cofactor(m, 0, 0);
	det += m->m[0][1] * matrix_cofactor(m, 0, 1);
	det += m->m[0][2] * matrix_cofactor(m, 0, 2);
	return det;
}

float det4x4(t_mat *m)
{
	float det = 0.0;
	t_mat3 sub;
	int j;

	j = 0;
	while (j < SIZE)
	{
		submatrix4x4(&sub, m, 0, j);
		float cofactor = det3x3(&sub);
		if (j % 2 != 0)
			cofactor = -cofactor;
		det += m->m[0][j] * cofactor;
		j++;
	}
	return det;
}

bool matrix_inverse(t_mat *out, t_mat *in)
{
	int row;
	int col;
	float det;
	float cofactor;
	t_mat3 sub;

	det = det4x4(in);
	if (det == 0.0)
		return false;
	row = 0;
	while (row < SIZE)
	{
		col = 0;
		while (col < SIZE)
		{
			submatrix4x4(&sub, in, row, col);
			cofactor = det3x3(&sub);
			if ((row + col) % 2 != 0)
				cofactor = -cofactor;
			out->m[col][row] = cofactor / det;
			col++;
		}
		row++;
	}
	return true;
}

