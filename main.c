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
	t_mat m1;
	rotate_z(&m1, M_PI / 4);
	matrix_print(&m1);
	return 0;
}
