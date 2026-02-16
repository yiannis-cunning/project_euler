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


#define FIRST_SEQ_DEPTH_LIMIT 10000
#define N_MAX (0x3FFFFFFFFFFFFFFF)


int sequence_size(int n_start, int depth_limit){
    int steps = 1;
    
    uint64_t n = (uint64_t) n_start;
    while(1){
        if(n == 1) return steps;
        if(steps > depth_limit) return depth_limit;
        passert(n < N_MAX, "overflow during sequence calcluation");

        if(n % 2 == 0) n = n >> 1;
        else n = n * 3 + 1;
        steps += 1;
    }

    return steps;
}


int find_largest_collatz (){


    // First narrow it down by checking all short sequences under 1 million
    int candidates[1024];
    int j = 0;

    int seq_size_max = 0;
    int i_max;
    
    for(int i = 1; i < 1000000; i += 1){

        int seq_size = sequence_size(i, FIRST_SEQ_DEPTH_LIMIT);
        //printf("Sequence size of %d = %d\n", i, seq_size);

        if(seq_size > seq_size_max){
            seq_size_max = seq_size;
            i_max = i;
        }

        if(seq_size == FIRST_SEQ_DEPTH_LIMIT){
            candidates[j++] = i;
            passert(j < 1024, "Overflow on candidates buffer");
        }
    }

    printf("Narrowed it down to %d numbers under 1 million.\n", j);
    printf("Biggest starting number = %d, size = %d\n", i_max, seq_size_max);

}


int main(){
    find_largest_collatz();

}