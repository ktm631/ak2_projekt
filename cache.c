#include <asm-generic/cacheflush.h>
#include <stdlib.h>
int main(){
	flush_cache_all();
	const int size = 0xff;
	char *c = (char *)malloc(size);
	for (int i = 0; i < 1000; i++)
 	 for (int j = 0; j < size; j++)
 	  c[j] = i*j;
	return 0;
}

