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


int sum_digits(uint64_t val){
    int ans = 0;
    while(val != 0){
        ans += (val % 10);
        val -= (val % 10);
        val = val/10;
    }
    return ans;
}

void simple_check(int n){
    int ans = 0;
    for(int i  = 0; i < n; i += 1){
        if(sum_digits(i) == sum_digits(137*i)){
            ans += 1;
        }
    }
    printf("Found %d values which satisfy this property, with n = %d\n", ans, n);

}


void make_data(int n_max){

    for(int i = 0; i < n_max; i += 1){
        printf("%d, %d\n", i, sum_digits(i));
    }

}


// sum_digis(n)

int main(){

    make_data(10000);
    /*
    int n = 10;
    while(1){
        simple_check(n);
        n = n *10;
    }*/


}
