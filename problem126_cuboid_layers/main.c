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

int main(){

    // new_blocks(itteration=1, start=(x, y,z)), what are bounds of x, y, z s.t. new_blocks < n
    // new_blocks(i, R) < new_blocks(i + 1, R)
    

    // new_blocks(1, (w, l, h)) = 2*w*h + 2*w*l + 2*l*h
    // new_blocks(2, (w, l, h)) = 2*w*h + 2*w*l + 2*l*h + w*4 + h*4 + l*4
    // new_blocks(3, (w, l, h)) = 2*w*h + 2*w*l + 2*l*h + w*4 + h*4 + l*4

    // new_blocks(n, w/l/h) = base + h*(n - 1)*4 + w*(n - 1)*4 + h*(n - 1)*4



    // For each n, 0 -> inf
    //      count = 0
    //      For each w, l, h set where f(1, r) < n
    //          Continue on itterations until new_blocks > n
    //          if(get n blocks) count += 1
    //          

}
