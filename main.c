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
	t_mat m;
	indentity(&m);
	t_object s;

	s.id = 1;
	s.radius = 1;
	s.type = 1;
	s.material = NULL;
	s.x = 0;
	s.y = 0;
	s.z = 0;
	s.transform = &m;

	t_ray r;
	t_tuple p, direction, pp;
	point(&p,2,3,4);
	vector(&direction,1,0,0);
	r.direction = &direction;
	r.origin = &p;

	position(&pp, &r, 2.5);

	tuple_print(&pp);
 	return 0;
}
