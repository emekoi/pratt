#include "util.h"

int string_casencmp(const char *s1, const char *s2, size_t n) {
	while(n > 0 && ((unsigned char)*s1) == ((unsigned char)*s2)) {
		if(*s1 == '\0') return 0;
		s1++;
		s2++;
		n--;
	}

	if(n == 0) return 0;
	return ((unsigned char)*s1) - ((unsigned char)*s2);
}
