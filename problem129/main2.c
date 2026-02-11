#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#define N_CHIPS 1000000
#define N_DEFECTS 20000

//#define VERBOSE

// Question 307

typedef struct probabilities {
    double arr[N_DEFECTS];
    
} probabilities_t;

typedef struct cord {
    int ones;
    int twos;
    int zeros;
    double prob; // in format of x/N_CHIPS
} cord_t;

// have_need[need_number][lsb]
// 1, 3, 7, 9
static uint32_t have_need[10][10] = {
{0,0,0,0,0,0,0,0,0,0},
{0,1,0,7,0,0,0,3,0,9},
{0,2,0,4,0,0,0,6,0,8},
{0,3,0,1,0,0,0,9,0,7},
{0,4,0,8,0,0,0,2,0,6},
{0,5,0,5,0,0,0,5,0,5},
{0,6,0,2,0,0,0,8,0,4},
{0,7,0,9,0,0,0,1,0,3},
{0,8,0,6,0,0,0,4,0,2},
{0,9,0,3,0,0,0,7,0,1}
};

void passert(bool cond, char *msg){
    if(!cond){
        printf("%s", msg);
        exit(1);
    }
}


// ... n100 n10 n1
// n1 = 1, 3, 7, 9
// Need = 1, 2, 3, 4, 5, 6, 7, 8, 9, 0



uint32_t a_of(uint32_t n){
    passert(n % 2 != 0, "N given is divisible by 2");
    passert(n % 5 != 0, "N given is divisible by 5");
    // How many times to multiply to get a 111's number
    // = 10**9 + 10**8 + 10**7
    // R(k) = 1111
    // R(k + 1) = R(k)*10 + 1


    uint32_t have = n % 10;
    uint32_t running_sum = 0;
    uint32_t num_ones = 0;
    uint32_t need = 0;

    while(running_sum != 1){
        need = (11 - (running_sum % 10))%10;
        running_sum += have_need[need][have]*n;
        running_sum = (running_sum - 1)/10;
        num_ones += 1;
        //printf("loop  - sum %d\n", running_sum);
        
    }

    return num_ones + 1;
}



int main(){



    int n = 999001;
    int xmax = 0;
    while(1){
        int x = a_of(n);
        if(x > xmax){
            printf("Found new x max. n =  %d, A(n) = %d\n", n, x);
            xmax = x;
        }
        n = n + 2;
        if(n % 5 == 0){
            n = n + 2;
        }
    }
    
    printf("Calculating A(n) for n = 3, %d\n", a_of(3) );
    printf("Calculating A(n) for n = 5, %d\n", a_of(7) );


}

// 473411 - 473410