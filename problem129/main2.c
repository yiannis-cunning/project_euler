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
static uint32_t have_need[10][4] = {
    {0,0,0,0},
    {1,7,3,9},
    {2,4,6,8},
    {3,1,9,7},
    {4,8,2,6},
    {5,5,5,5},
    {6,2,8,4},
    {7,9,1,3},
    {8,6,4,2},
    {9,3,7,1}
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
    passert(n % 5 != 0, "N given is divisible by 2");
    // How many times to multiply to get a 111's number
    // = 10**9 + 10**8 + 10**7
    // R(k) = 1111
    // R(k + 1) = R(k)*10 + 1


    while(running_sum != 1s)
}



int main(){



    printf("Probability of a chip having 3+ defects for %d chips, %d defects = %.12f\n" );


}