#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

void passert(bool cond, char *msg){
    if(!cond){
        printf("%s\n", msg);
        exit(1);
    }
}



int find_solutions(uint64_t n){
    // Find solutions given y
    //  n < x < n**2 + n

    int solutions = 0; // x = y = 2n

    for(uint64_t x = n + 1; x <= 2*n; x += 1){
        uint64_t top = x*n;
        uint64_t bot = x - n;
        if( top % bot == 0){
            solutions += 1;
           //printf("found x = %d, x - n = %d\n", x, x- n);


        }

        //printf("top %d, bot %d\n", top, bot);
    }

    return solutions;
}

/*
void try_primes(){
    // check all numbers less than below
    // 2*3*5*7*11*13*17;
    // a0, a1, a2, a3, a4, a5, a6
    // decreasing values
    // sum < 7

    // 1
  
    // 1, 1
    // 2

    // 1, 1, 1
    // 2, 1
    // 3

    // 1, 1, 1, 1
    // 2, 1, 1
    // 2, 2
    
    

    uint64_t primes = {2, 3, 5, 7, 11, 13, 17};



    for(int npoints = 0; npoints <= 7; npoints+=1){
        int cofs[7]  = {0};
        while(iterate(cofs)){
            uint64_t val = 0;
        }
       

    }

}

*/

bool itterate(int *powers, int n){


}


int fact_to_num(int * powers, int npowers){
    int ans = 1;
    int primes[7] = {2, 3, 5, 7, 11, 13, 17};
    for(int i=0; i < npowers; i += 1){
        ans = ans*primes[i];
    }

    return ans;
}

int get_solutions(int * powers, int npowers){
    int ans = 1;
    for(int i=0; i < npowers; i += 1){
        ans = ans*(powers[i]*2 + 1);
    }
    return (ans >> 1) + 1;
}

int main(){


    int n = 2*2*3*3*5*5/10;
    int ans = find_solutions(n);
    int f[4] = {1, 2, 1, 0};
    int ans2 = get_solutions(f, 4);
    printf("Found %d solutions for n=%d or %d\n", ans, n, ans2);
    n = 1000;


    int factors[7] = {1, 1, 1, 1, 1, 1, 1};


    printf("Solutions for 7 primes = %d\n", get_solutions(factors, 7));

    int maximum = fact_to_num(factors, 7);

    while(1){
       int slns = get_solutions(factors, 7);
       int val = fact_to_num(factors, 7);
       if(slns > 1000 && val < maximum){
           maximum = val;

       }
       // itterate factors
       


    }    

    return 0;
    // 7  6, 4, 3, 2 -> 1008 facors
    // 6, 5, 3, 3, 2, 2 -> 1080
    // 6, 5, 3, 3, 2, 2
    uint64_t upper_bound = (1 << 6)*(3*3*3*3*3)*(5*5*5)*(7*7)*(11);

    upper_bound = (2*2*2*2*2)*(3*3*3*3)*(5*5)*(7*7)*(11)*(13);

    uint64_t upper_upper_bound = 2*3*5*7*11*13*17;
    upper_upper_bound = upper_upper_bound;


    printf("upper bound = %ld, solutions %d\n", upper_bound, find_solutions(upper_bound));

    printf("upper upper bound = %ld, solutions = %ld\n", upper_upper_bound, find_solutions(upper_upper_bound));
    return 1;
    // n > 8218
    while(1){
        int s = find_solutions(n);
        if(s > 1000){
            printf("Found a n = %d\n", n);
            return 1;
        }
        //printf("n = %d, s = %d\n", n, s);
        n += 1;
    }

}
