# include "include/miniRt.h"

int main(void)
{
	t_tuple t1,t2;

	point(&t2,1,-2, 3);
	tuple_divide_scalor(&t1, &t2, 2.0);
	tuple_print(&t1);
	return (0);
}
