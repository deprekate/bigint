# bigint
An implementation of a fixed point integer datatype for the C programming language.


BigInt is just a single header file: bigint.h. All you need to do is copy the header file into your project, and:
```sh
#include "uthash.h"
```
Since bigint is a header file only, there is no library code to link against.


Example 1. Adding two numbers.
```sh
#include "bigint.h""

char *a = "100000000000000000000000000000000000000000000000000000000000000000000";
char *b = "-5";

bigint *x = bi_from_string(a);
bigint *y = bi_from_string(b);
bigint *z = bi_add(x, y);
```

Example 2. Subtracting two numbers.
```sh
#include "bigint.h""

char *a = "100000000000000000000000000000000000000000000000000000000000000000000";
char *b = "-5";

bigint *x = bi_from_string(a);
bigint *y = bi_from_string(b);
bigint *z = bi_sub(x, y);
```

Example 3. Comparing two numbers.
```sh
#include "bigint.h""

char *a = "100000000000000000000000000000000000000000000000000000000000000000000";
char *b = "-5";

bigint *x = bi_from_string(a);
bigint *y = bi_from_string(b);
if(bi_cmp(x,y)){
	printf("% is larger\n", bi_to_string(x));
}else{
	printf("% is larger\n", bi_to_string(y));
} 
```
