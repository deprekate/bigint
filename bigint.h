/* 

    bigint

    Copyright (C) 2017 Katelyn McNair and Robert Edwards

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static int mod(int a, int b){
        int c = a % b;
        return c < 0 ? c + b : c;
}

typedef struct bigint{
	bool positive;
	size_t size;
	unsigned char data[];
} bigint;
extern const bigint BI_INF;

static bigint* bi_new(size_t size){
	bigint *b = calloc(sizeof(*b) + size, 1);
	if(b){
		b->size = size;
	}
	b->positive = true;
	return b;
}

bigint* bi_inf(void){
	size_t max_size = (size_t)-1;
	bigint *b = bi_new(max_size);
	return b;
}


static bigint* bi_from_string(const char *s){
	bigint *b;
	bool positive = true;

	if(s[0] == '-'){
		positive = false;
	}
	s += strspn(s, "-");
	s += strspn(s, "0");
	if(strstr(s, "E+") != NULL){
		char *tok, *str, *m, *ptr;
		int i, num, offset, n, min;
		size_t size;

		str = malloc(strlen(s) + 1);
		strcpy(str, s);
		tok = strtok(str, "E+");
		m = malloc(strlen(tok) + 1);

		offset = 0;
		for(i = 0; tok[i] != '\0'; i++){
			if(tok[i] != '.'){
				m[i-offset] = tok[i];
			}else{
				offset = 1;
				num = i;
			}
		}
		tok = strtok(NULL, "E+");
		n = strtol(tok, &ptr, 10);
		size = num+n;
		min = strlen(m) < num+n ? strlen(m) : num+n;
		printf("%i %i\n", num, n);
		b = bi_new(num+n);

		for(i = 0; i < min; i++){
			b->data[size - i - 1] = m[i] - '0';
		}
		free(str);
		free(m);
	}else if(strstr(s, "E-") != NULL || strstr(s, ".") != NULL){
		b = bi_new(1);
	}else{
		size_t size = strlen(s);
		int min = (size == 0) ? 1 : 0;

		b = bi_new(size + min);
		int i;
		for(i = 0; i < size; i++){
			b->data[size - i - 1] = s[i] - '0';
		}
	}
	b->positive = positive;
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
	bool val;
	if(a->positive == b->positive){
		if(a->size > b->size){
			return a->positive;
		}else if(a->size < b->size){
			return !a->positive;
		}else{
			size_t max = (a->size > b->size ? a->size : b->size);
			int i;
			for(i=0; i<=max; ++i){
				if(a->data[i] > b->data[i]){
					return a->positive;
				}else{
					return false;
				}
			}
		}
	}else{
		return a->positive;
	}
}






