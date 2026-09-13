
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


// Triangle - a, a+-1, ~ a*sqrt(3)/2
// Such that a + b + c = area



// a + a + a + 1 < 10**9
//  3a + 1 < 10**9
// a + a + a - 1 < 10**9
//  3a - 1 < 10**9

// a < floor((10**9) + 1)/3


// Find h s.t.
//     - a**2 - (b/2)**2 = whole**2

void passert(bool cond, char *msg){
    if(!cond){
        printf("%s", msg);
        exit(1);
    }
}


uint32_t check_intergral(uint32_t a, uint32_t b, uint32_t h){
    uint32_t perim = a*2 + b;
    uint32_t area = b*h >> 1;

    if(area == perim){
        printf("Found a trig at %d/%d/%d\n", a, b, h);
        return perim;
        
    }

    return 0;
}


#define A_MAX 333333333
#define A_MAX 100000


/*
    var x, x_sqared;

    x_squared = x_squared + 2*x + 1
    x = x + 1


(x + 2)**2 = x**2 + 4*x + 4

*/

int main(){

    uint32_t a = 3;
    uint64_t a_squared = 9;

    uint32_t bm = 2;
    uint32_t bm_div2 = 1;
    uint64_t bm_div2_squared = 1;

    uint32_t bp = 4;
    uint32_t bp_div2 = 2;
    uint64_t bp_div2_squared = 4;

    uint32_t h_upper = 3;
    uint64_t h_upper_squared = 9;
    uint32_t h_lower = 2;
    uint64_t h_lower_squared = 4;

    
    uint32_t perim_sum = 0;

    while(a <= A_MAX){

        // Calculate next trig from current
        a_squared = a_squared + 4*a + 4;
        a += 2;

        bm_div2_squared = bm_div2_squared + 4*bm_div2 + 4;
        bm += 2;
        bm_div2 += 1;

        bp_div2_squared = bp_div2_squared + 4*bp_div2 + 4;
        bp += 2;
        bp_div2 += 1;

        // Update H range

        // Check if h is whole
        // lhsp < lhs_m
        uint64_t lhs_m = a_squared - bm_div2_squared; // 8
        uint64_t lhs_p = a_squared - bp_div2_squared; // 5

        // Check lhs in h range
        if(lhs_p == h_upper_squared){
            perim_sum += check_intergral(a, bp, h_upper);
        } else if (lhs_p == h_lower_squared){
            perim_sum += check_intergral(a, bp, h_lower);
        } else if (lhs_m == h_upper_squared){
            perim_sum += check_intergral(a, bm, h_upper);
        } else if (lhs_m == h_lower_squared){
            perim_sum += check_intergral(a, bm, h_lower);
        }

        // Adjust h range
        while(lhs_p > h_lower){
            // Update H values
            h_lower_squared = h_upper_squared;
            h_lower = h_upper;

            h_upper_squared = h_upper_squared + 2*h_upper + 1;
            h_upper = h_upper + 1;

        }

        // Check lhs in h range
        if(lhs_p == h_upper_squared){
            perim_sum += check_intergral(a, bp, h_upper);
        } else if (lhs_p == h_lower_squared){
            perim_sum += check_intergral(a, bp, h_lower);
        } else if (lhs_m == h_upper_squared){
            perim_sum += check_intergral(a, bm, h_upper);
        } else if (lhs_m == h_lower_squared){
            perim_sum += check_intergral(a, bm, h_lower);
        }

    }


}