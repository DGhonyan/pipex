#include "pipex.h"
#include <stdio.h>

void	error_case(char *errmsg, int (*f)(), int type)
{
	perror(errmsg);
	//printf("%d", f(1, 2));
	if (type == 1)
		f()
	
}

int a(int a, int b)
{
	return a + b;
}

int main(void)
{
	error_case("aaaa", &a);
}
