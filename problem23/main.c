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


#define N_MAX 28123


uint32_t sum_proper_factors(uint32_t n){
    uint32_t sum = 0;
    for(uint32_t i = 1; i <= (n >> 1); i += 1){
        if(n % i == 0) sum += i;
    }
    return sum;
}

// Do they have to be different?
// nums is sorted based on size
bool sumable(uint32_t n, uint32_t *nums, int n_nums){

    int i = 0;
    int j = 0;

    while(nums[i] < n){
        j = 0;
        while (j <= i){
            if(nums[i] + nums[j] == n) return true;
            j += 1;
        }
        i += 1;
    }
    return false;
}

int main(){

    int num_abundants = 0;
    uint32_t abundants[7000];

    // Find all abundant numbers less than N_MAX
    for(uint32_t i = 2; i < N_MAX; i += 1){
        uint32_t s = sum_proper_factors(i);
        if(s > i) {
            //printf("ABUNDANT ");
            //printf("i = %d, sum_factors = %d\n", i, s);
            abundants[num_abundants++] = i;
        }
    }

    //printf("Found %d abundanat numbers under %d\n", num_abundants, N_MAX );
    //return 0;

    // Check all numbers less than N_MAX if they can be the sum of 2 abundants
    int sum = 0;
    for(uint32_t i = 1; i <= N_MAX; i += 1){
        if(!sumable(i, abundants, num_abundants)){
            sum += i;
        }
    }

    printf("Sum of all numbers that connot be written as the sum of 2 abundant numbers: %d\n", sum);

}