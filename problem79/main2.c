#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>


#include "rules.h"

// rules = { ... {a, b, c}, ... }


bool check_rule(uint8_t *rule, uint8_t *num, int numlen){
    int j = 0;

    for(int i = 0; i < numlen; i += 1)
    {
        if(num[i] == rule[j])
        {
            if(j == 2){
                return true;
            }
            j += 1;
        }
    }

    return false;
}


bool check_rules(uint8_t *num, int numlen){


    for(int ri = 0; ri < n_rules; ri += 1){
        uint8_t * rule = rules_real[ri];

        if(!check_rule(rule, num, numlen)){
            printf("Error with number %d\n", ri);
            printf("%d, %d, %d\n", rule[0], rule[1], rule[2]);
            return false;
        }
    }
    return true;
}

int main(){

    //uint8_t num[] = {8, 1, 7, 3, 6, 1, 2, 9, 8, 0, 9, 6};
    uint8_t num[] = {7, 3, 1, 6, 2, 8, 9, 0};
    int numlen = 9;

    printf("This number is %d\n", check_rules(num, numlen));

    for(int i =0; i< 16777216; i += 1){
        break;
        check_rules(num, numlen);
        //printf(i);
    }

}