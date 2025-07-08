# include "include/miniRt.h"

int main(void)
{
	t_tuple p;
	point(&p, 2.0,3.0,4.0);
	printf("after calling point : \n");
	printf("p.x : %.2f\n", p.t[0]);
	printf("p.y : %.2f\n", p.t[1]);
	printf("p.z : %.2f\n", p.t[2]);
	printf("p.w : %.2f\n", p.t[3]);

	color(&p, 5.0,6.0,7.0);
	printf("after calling color : \n");
	printf("p.x : %.2f\n", p.t[0]);
	printf("p.y : %.2f\n", p.t[1]);
	printf("p.z : %.2f\n", p.t[2]);
	printf("p.w : %.2f\n", p.t[3]);

	vector(&p, 8.0, 9.0, 1.0);
	printf("after calling vector : \n");
	printf("p.x : %.2f\n", p.t[0]);
	printf("p.y : %.2f\n", p.t[1]);
	printf("p.z : %.2f\n", p.t[2]);
	printf("p.w : %.2f\n", p.t[3]);
	return (0);
}
