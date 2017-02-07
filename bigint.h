#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int mod(int a, int b){
        int c = a % b;
        return c < 0 ? c + b : c;
}

typedef struct{
	bool positive;
	size_t size;
	unsigned char data[];
} bigint;

static bigint* bi_new(size_t size){
	bigint *b = calloc(sizeof(*b) + size, 1);
	if(b){
		b->size = size;
	}
	b->positive = true;
	return b;
}

static bigint* bi_from_string(const char *s){
	bool positive = true;
	if(s[0] == '-'){
		positive = false;
	}
	s += strspn(s, "-");
	s += strspn(s, "0");
	size_t size = strlen(s);
	int min = (size == 0) ? 1 : 0;

	bigint *b = bi_new(size + min);
	b->positive = positive;
	int i;
	for(i = 0; i < size; i++){
		b->data[size - i - 1] = s[i] - '0';
	}
	return b;
}
char *bi_to_string(bigint *a){
	char *b = malloc(a->size * sizeof(char) + 1);
	if(a->positive){
		b[0] = '+';
	}else{
		b[0] = '-';
	}
	int i;
	for(i = 1; i <= a->size; i++){
		b[i] = a->data[a->size - i] + '0';
	}
	return b;
}
static bigint* _bi_sub(const bigint *a, const bigint *b){
	size_t max = (a->size > b->size ? a->size : b->size);
	bigint *c;
	c = bi_new(max);
	int carry = 0;
	int i;
	for(i=0; i<max; ++i){
		int tmp = carry;
		if(i < a->size){
			tmp += a->data[i];
		}
		if(i < b->size){
			tmp -= b->data[i];
		}
		carry = tmp < 0 ? -1 : 0;
		c->data[i] = mod(tmp, 10);
	}
	return c;
}
static bigint* _bi_add(const bigint *a, const bigint *b){
	size_t max = (a->size > b->size ? a->size : b->size);
	bigint *c;
	c = bi_new(max + 1);
	int carry = 0;
	int i;
	for(i=0; i<max; ++i){
		int tmp = carry;
		if(i < a->size){
			tmp += a->data[i];
		}
		if(i < b->size){
			tmp += b->data[i];
		}
		carry = tmp / 10;
		c->data[i] = tmp % 10;
	}
	if(carry){
		c->data[i] = 1;
	}else{
		c->size--;
	}
	return c;
}
bigint* bi_sub(const bigint *a, const bigint *b){
	bigint *c;
	if(a->positive == b->positive){
		c = _bi_sub(a, b);
	}else if(a->positive){
		c = _bi_add(a, b);
	}else{
		c = _bi_add(a, b);
		c->positive = false;
	}
	return c;
}

bigint* bi_add(const bigint *a, const bigint *b){
	bigint *c;
	if(a->positive == b->positive){
		c = _bi_add(a, b);
	}else if(a->positive){
		c = _bi_sub(a, b);
	}else{
		c = _bi_sub(a, b);
		c->positive = false;
	}
	return c;
}
bool bi_cmp(const bigint *a, const bigint *b){
	if(a->positive == b->positive){
		if(a->positive){
			if(a->size > b->size){
				return true;
			}else if(a->size < b->size){
				return false;
			}
		}else{
			if(a->size > b->size){
				return false;
			}else if(a->size < b->size){
				return true;
			}
		}
	}else{
		if(a->positive){
			return true;
		}else{
			return false;
		}
	}

}






