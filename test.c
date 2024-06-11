#include <stdio.h>
#include <sys/time.h>

int main()
{
	struct timeval tval;
	printf("%d\n", gettimeofday(&tval, NULL));
	printf("sec: %ld\nusec: %d\n", tval.tv_sec, tval.tv_usec);
	return (0);
}