#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "nCr.h"

int main (int argc, char **argv) {
	int n;
	int r;
	int t;
	int constant;
	struct timeval begin, end;

	if(argc != 2) {
		fprintf(stderr, "ERROR, invalid number of arguments (Usage: formula <power> \n");
		return 0;
	}else if(argv[1][0] == '-' && argv[1][1] == 'h') {
		printf("Usage: formula <positive integer> \n");
		return 0;
	}else if(argv[1][0] == '-'){
		printf("Usage: formula <positive integer> \n");
		return 0;
	}
	n = atoi(argv[1]);
	//detects overflow
	gettimeofday(&begin, NULL);
	for(r = 0 ; r <= n; r++) {
		constant = nCr(n, r);
		if (constant < 0) {
			fprintf(stderr, "ERROR: overflow detected \n");
			return 0;
		}
	}
	printf("(1 + x)^%i = ", n);
	
	/*for each increment a constant is computed through function nCr and prints the solution */
	for(r = 0 ; r <= n; r++) {
		constant = nCr(n, r);
		if(r == 0) {
			printf ( "1 ");
			if (r != n) {
				printf("+");
			}
			continue;
		} else if ( r > 0 && r < n); {
			
			printf( " %i*x^%i ", constant, r);
		} 
		if (r != n) {
			printf("+");
		}
	}
	printf("\n");
	gettimeofday(&end,NULL);
	t = (( end.tv_usec) - ( begin.tv_usec));
	printf("Time Required = %i microseconds\n", t);
	return 0;
}



