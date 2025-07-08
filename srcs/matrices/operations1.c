# include "../../include/miniRt.h"

void matrix(t_mat *m)
{
	int row;
	int column;

	row = 0;
	column = 0;
	while(column < SIZE)
	{
		row = 0;
		while(row < SIZE)
		{
			m->m[column][row] = 0.0;
			row++;
		}
		column++;
	}
}

void matrix_print(t_mat *mt)
{
	int row;
	int column;

	row = 0;
	column = 0;
	while(column < SIZE)
	{
		row = 0;
		while(row < SIZE)
		{
			printf(" | m[%d][%d] : %8.5f", column, row, mt->m[column][row]);
			row++;
		}
		printf("\n");
		column++;
	}
}

void matrix_multiply(t_mat *m0, t_mat *m1, t_mat *m2)
{
	int column;
	int row;
	int k;

	column = 0;
	while (column < SIZE)
	{
		row = 0;
		while (row < SIZE)
		{
			m0->m[column][row] = 0.0;
			k = 0;
			while (k < SIZE)
			{
				m0->m[column][row] += m1->m[column][k] * m2->m[k][row];
				k++;
			}
			row++;
		}
		column++;
	}
}

void indentity(t_mat *m0)
{
	m0->m[0][0] = 1.0;
	m0->m[1][1] = 1.0;
	m0->m[2][2] = 1.0;
	m0->m[3][3] = 1.0;
}

void matrix_transpose(t_mat *m0, t_mat *m1)
{
	int row;
	int column;

	row = 0;
	column = 0;
	while(column < SIZE)
	{
		row = 0;
		while(row < SIZE)
		{
			m0->m[column][row] = m1->m[row][column];
			row++;
		}
		column++;
	}
}
