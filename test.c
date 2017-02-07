#include <stdio.h>
#include "bigint.h"

int main() {
	char *a = "-1234";
	char *b = "-5";

	bigint *x = bi_from_string(a);
	bigint *y = bi_from_string(b);
	bigint *z = bi_sub(x, y);
	printf("%s\n", bi_to_string(z));
	if(bi_cmp(x,y)){
		printf("true\n");
	}else{
		printf("false\n");
		
	}
}

