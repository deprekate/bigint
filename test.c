#include <stdio.h>
#include "bigint.h"

int main() {
	char *a = "100000000000000000000000000000000000000000000000000000000000000000000";
	char *b = "-5";


	bigint *x = bi_from_string(a);
	bigint *y = bi_from_string(b);
	bigint *z = bi_add(x, y);
	printf("%s + %s = %s\n", bi_to_string(x), bi_to_string(y), bi_to_string(z));

	printf("\n\n");
	
	printf("Is %s greater than %s\n", bi_to_string(x), bi_to_string(y));
	if(bi_cmp(x,y)){
		printf("true\n");
	}else{
		printf("false\n");
		
	}
}

