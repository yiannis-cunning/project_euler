#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

void passert(bool cond, char *msg){
    if(!cond){
        printf("%s\n", msg);
        exit(1);
    }
}

bool isprime(uint32_t x){
    
    uint32_t lim = 1 + (uint32_t)sqrt(x);

    if(x == 1) return false;

    for(uint32_t i = 2; i < x; i += 1){
	if(i > lim) break;

        if(x % i == 0) return false;
    }

    return true;
}

int main(){

    uint64_t n = 2;
    uint32_t found = 2;
    bool d0, d1, d2, q0, q1, q2;


    d0 = isprime(6*n + 1);
    d1 = isprime(6*n - 1);
    d2 = isprime(12*n + 5);

    q0 = isprime(6*n + 5);
    q1 = isprime(6*n - 1);
    q2 = isprime(12*n - 7);

    uint64_t ans;

    while(1){
	if(d0 && d1 && d2) found += 1;

        if(found == 2000){ans = 2+ 3*n*(n-1); break;}

	if(q0 && q1 && q2) found += 1;

        if(found == 2000){ans = 1+ 3*n*(n+1); break;}

	n = n + 1;
	// calculate n + 1 vals	
        q1 = q0;
	d1 = q0;
	q2 = d2;

	d0 = isprime(6*n + 1);
	q0 = isprime(6*n + 5);
        d2 = isprime(12*n + 5);

    }
   printf("found %d nums with n=%ld, last = %ld\n", found, n, ans);


    return 0;
}
