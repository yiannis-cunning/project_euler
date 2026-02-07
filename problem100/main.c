#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#define VERBOSE

void passert(bool cond, char *msg){
    if(!cond){
        printf("%s", msg);
        exit(1);
    }
}





typedef struct uint128{
    uint64_t msb;
    uint64_t lsb;
} uint128;


uint128 expand(uint64_t a){
    return (uint128) {0, a};
}

uint128 ls2(uint128 a){
    passert((a.msb >> 63) != 1, "Overflow during x2 operation");

    uint128 x = {(a.msb << 1) + (a.lsb >> 63), a.lsb << 1};

    return x;
}


uint128 add(uint128 a, uint128 b){
    uint128 x = {0};
    x.lsb = a.lsb + b.lsb;

    if(x.lsb < a.lsb && x.lsb < b.lsb){ // overflow by 1
        x.msb = a.msb + b.msb + 1;
    } else{
        x.msb = a.msb + b.msb;
    }
    passert(x.msb >= a.msb & x.msb >= b.msb, "Error overflow in add operation");
    return x;
}

uint128 minus(uint128 a, uint128 b){

    uint128 x = {a.msb - b.msb, a.lsb - b.lsb};

    if(b.lsb > a.lsb){
        passert(x.msb > 0, "ERROR: Underflow on subtraction");
        x.msb = x.msb - 1;
    }
    return x;
}

// No overflow possible
uint128 multiply(uint64_t a, uint64_t b){
    // (a.lsb + a.msb*2**32)*(b.lsb + b.msb*2**32) 
    // uint32_t ^ 2 < 2**32 ^2 < 2**64 ?

    uint64_t a_lsb = a & 0xFFFFFFFF;
    uint64_t a_msb = (a >> 32) & 0xFFFFFFFF;

    uint64_t b_lsb = b & 0xFFFFFFFF;
    uint64_t b_msb = (b >> 32) & 0xFFFFFFFF;

    uint128 x = {a_msb*b_msb, a_lsb*b_lsb};
    uint128 y = {a_lsb*b_msb >> 32, a_lsb*b_msb << 32}; // *2^32
    uint128 z = {a_msb*b_lsb >> 32, a_msb*b_lsb << 32}; // *2^32

    return add(x, add(y, z));

}

bool gt_128(uint128 a, uint128 b){
    if(a.msb == b.msb){
        return a.lsb > b.lsb;
    }
    return a.msb > b.msb;
}


bool eq_128(uint128 a, uint128 b){
    return (a.lsb == b.lsb) & (a.msb == b.msb);
}







uint64_t self_sqrt(uint128 number){


    uint64_t guess = 0;
    uint128 guess_squared = {0, 0};

    for(int bit = 63; bit >= 0; bit -= 1)
    {
        // set bit to 1
        guess = guess | (0x1 << bit);

        guess_squared = multiply(guess, guess);

        if( (guess_squared.msb == number.msb) && (guess_squared.lsb == number.lsb) ){
            return guess;
        }

        if(gt_128(guess_squared, number))
        {
            guess = guess & (~(0x1 << bit)); // set it to 0
        }
    }

    if( (guess_squared.msb == number.msb) && (guess_squared.lsb == number.lsb) ){
        return guess;
    }
    return 0;
}
/*k*(k-1)/n*(n-1)

2*k*(k-1) = n*(n-1)*/

uint64_t works(uint64_t n){


    #ifdef VERBOSE
    printf("x = %lx - %lx \n", 0, n);
    #endif
    uint128 n_sqr = multiply(n, n); //n*n

    #ifdef VERBOSE
    printf("x = %lx - %lx \n", n_sqr.msb, n_sqr.lsb);
    #endif
    uint128 n_sqr_minus = minus(n_sqr, expand(n));          // n*n - n
    #ifdef VERBOSE
    printf("x = %lx - %lx \n", n_sqr_minus.msb, n_sqr_minus.lsb);
    #endif
    uint128 n_sqr_minus_x2 = ls2(n_sqr_minus);              // (n*n - n)*2
    
    #ifdef VERBOSE
    printf("x = %lx - %lx \n", n_sqr_minus_x2.msb, n_sqr_minus_x2.lsb);
    #endif

    uint128 square_in = add(n_sqr_minus_x2, expand(1));     // (n*n - n)*2 + 1
    
#ifdef VERBOSE
    printf("x = %lx - %lx \n", square_in.msb, square_in.lsb);
#endif

    uint64_t square_out = self_sqrt( square_in);


#ifdef VERBOSE
    printf("x = %lx - %lx \n", 0, square_out);
#endif

    if(square_out == 0){
        return 0;
    }

    if((square_out & 0x1) == 0){ // Need it to be odd
        return 0;
    }

    return (1 + square_out) >> 1;


    /*
    uint64_t squarein = 1 + 2*(n*n - n);

    printf("%ld\n", squarein);
    double squareout = sqrt(squarein);

    uint64_t squareout_int = (uint64_t) squareout; // rounds down?
    double squareout_int_double = squareout - ((double) squareout_int);

    if(squareout_int_double > 0.0000000001){
        return 0;
    }

    if((squareout_int & 0x1) == 0){ // Need it to be odd
        return 0;
    }

    return (1 + squareout_int) >> 1;*/

}

bool check_combo(uint64_t k, uint64_t n){
    uint128 k_big = expand(k);
    uint128 n_big = expand(n);

    k_big = minus(multiply(k, k), k_big);
    n_big = minus(multiply(n, n), n_big);
    k_big = ls2(k_big);

    if( (k_big.msb == n_big.msb) && (k_big.lsb == n_big.lsb) ){
        return true;
    }

}

uint128 nsqrmn(uint64_t x){
    return minus(multiply(x, x), expand(x));
}




// find n, k s.t. n*n - n = 2*(k*k - k)
uint64_t find_match(uint64_t start_n, uint64_t start_k){

    uint64_t k = start_k + 1;
    uint128 klower = ls2(nsqrmn(start_k));
    uint128 kupper = ls2(nsqrmn(k)); // =f(k)





    uint64_t n = start_n;
    uint128 fn = nsqrmn(n);

#ifdef VERBOSE
    printf("x = %lx - %lx \n", klower.msb, klower.lsb);
#endif

#ifdef VERBOSE
    printf("x = %lx - %lx \n", kupper.msb, kupper.lsb);
#endif
#ifdef VERBOSE
    printf("x = %lx - %lx \n", fn.msb, fn.lsb);
#endif

    while(1){
        if(eq_128(fn, klower) || eq_128(fn, kupper)){
            printf("N = %ld, k = %ld works (or k+1)\n", n, k);
            exit(1);
        }

        passert(!gt_128(fn, kupper), "fn is greater than kupper");
        passert(gt_128(fn, klower), "fn is less than klower");
        
        fn = add(fn, expand(n << 1)); // f(n + 1)
        n = n + 1;

        if(gt_128(fn, kupper)){
            klower.lsb = kupper.lsb; klower.msb = kupper.msb; // klower = kupper
            kupper = add(kupper, expand(k << 2)); // + 4k
            k = k + 1;
        }


        #ifdef VERBOSE
    printf("klower = %lx - %lx \n", klower.msb, klower.lsb);
#endif

#ifdef VERBOSE
    printf("kupper = %lx - %lx \n", kupper.msb, kupper.lsb);
#endif
#ifdef VERBOSE
    printf("fn = %lx - %lx \n", fn.msb, fn.lsb);
#endif
        exit(1);

        if(n %100000000 == 0){
            printf("at N = %lx\n", n);
        }
    }
}


int main(){
    uint64_t n = 1000000000000;

    find_match(n, 707106781186);
    while(1){
        uint64_t k = works(n);
        printf("%d", n);
        if(k != 0){
            printf("N = %ld, k = %ld works\n", n, k);
            //return 0;
        }
        //exit(1);
        if(n %10000000 == 0){
            printf("at N = %lx\n", n);
        }
        n += 1;
    }

/*
    uint64_t k_bot = 1414213562373;
    uint64_t k_top = k_bot + 1;

    while(1){
        uint64_t k_top = works(n);
        uint64_t k_bot
        //printf("%d", n);
        if(k != 0){
            printf("N = %ld, k = %ld works\n", n, k);
            //return 0;
        }
        //exit(1);
        if(n %10000000 == 0){
            printf("at N = %lx\n", n);
        }
        n += 1;
    }*/

    
}
