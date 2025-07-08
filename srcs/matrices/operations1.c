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
			printf("m[%d][%d] : %.2f\t", column, row, mt->m[column][row]);
			row++;
		}
		printf("\n");
		column++;
	}
}

void matrix_multiply(t_mat *m0, t_mat *m1, t_mat *m2)
{
	int row;
	int column;
	int k;

	row = 0;
	column = 0;
	k = 0;
	while(column < SIZE)
	{
		row = 0;
		while(row < SIZE)
		{
			while(k < SIZE)
			{
				m0->m[column][row] += m1->m[column][k] + m2->m[k][row];
				k++;
			}
			row++;
		}
		column++;
	}
}
