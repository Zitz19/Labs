#include <stdio.h>
#include <math.h>


int main() {
	double x, e;
	printf("Enter x\n");
	scanf("%lf", &x);
	double ans = x;
	printf("Enter e\n");
	scanf("%lf", &e);
	double sin_x = sin(x);
	printf("Sin(x) from function'six(x)'\n");
	printf("%.15lf\n", sin_x);
	int i = 0;
	while (fabs(ans) - fabs(sin_x) > e) {
		i = i + 1;
		ans = ans*(1-((x*x)/(i*i*M_PI*M_PI)));
	}
	printf("Sin(x) from formula\n");
	printf("%.15lf\n", ans);
	printf("Number of itterations is %d\n", i);
	return 0;
}
