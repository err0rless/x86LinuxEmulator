#include <stdio.h>
#include <stdlib.h>

typedef struct aa
{
	long data;
} w;

int main(void)
{
	long a;
	void *v =malloc(4);

	memcpy(v, "\xf0\x00\x00\x00", 4);

	memcpy(&a, v, 4);

	printf("%ld\n", a);
}
