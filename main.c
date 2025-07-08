# include "include/miniRt.h"

void matrix_pnt(t_mat2 *mt)
{
	int row;
	int column;

	row = 0;
	column = 0;
	while(column < SIZE -2)
	{
		row = 0;
		while(row < SIZE -2)
		{
			printf(" | m[%d][%d] : %6.2f", column, row, mt->m[column][row]);
			row++;
		}
		printf("\n");
		column++;
	}
}

int main(void)
{
	t_mat m1,m2;
	m1.m[0][0] = 9;
	m1.m[0][1] = 3;
	m1.m[0][2] = 0;
	m1.m[0][3] = 9;
	m1.m[1][0] = -5;
	m1.m[1][1] = -2;
	m1.m[1][2] = -6;
	m1.m[1][3] = -3;
	m1.m[2][0] = -4;
	m1.m[2][1] = 9;
	m1.m[2][2] = 6;
	m1.m[2][3] = 4;
	m1.m[3][0] = -7;
	m1.m[3][1] = 6;
	m1.m[3][2] = 6;
	m1.m[3][3] = 2;

	matrix_inverse(&m2, &m1);
	matrix_print(&m2);
	return 0;
}
