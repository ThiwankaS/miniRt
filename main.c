# include "include/miniRt.h"

int main(void)
{
	t_tuple t0,t1,t2;

	vector(&t1, 1, 2, 3);
	vector(&t2, 2, 3, 4);
	cross(&t0,&t2,&t1);
	tuple_print(&t0);
	return (0);
}
