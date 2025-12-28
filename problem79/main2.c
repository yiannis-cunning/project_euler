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


void passert(bool cond, char *msg){
    if(!cond){
        printf("%s", msg);
        exit(1);
    }
}

void print_tree(double *arr, uint64_t div_factor, int n_defects){
    int row_size = 0;
    if( (n_defects % 2) == 0){      // Even = N/2 + 1
        row_size = (n_defects >> 1) + 1;
    } else{                         // Odd = (N + 1)/2
        row_size = ((n_defects + 1) >> 1);
    }


    for(int i = 0; i < row_size; i += 1){
        printf("%lf\t", arr[i]);
    }
    printf(" (factor = %ld)\n\n", div_factor);
}

// Compute the n_defects level given a array of n_defects + 1
int compute_n_minus_1( probabilities_t *prob, int n_defects){

    double *arr = prob->arr;

    // First pos = n_defects + 1 ones, 0 twos
    // Last poss

    cord_t left, right, self;

    //src_ptr[0] = self.ones/N_CHIPS * (right.prob) + self.twos/N_CHIPS *1 + (1 - self.ones/N_CHIPS - self.twos/N_CHIPS)*(left.prob);
    //arr[src_ptr] = right.prob*((float) self.ones)/N_CHIPS +  ((double) (N_CHIPS - self.ones - self.twos))*(left.prob)/N_CHIPS;
    //arr[src_ptr] = self.ones*right.prob +  self.zeros*left.prob + self.twos*N_CHIPS;
    // src_ptr[0] = self.ones/N_CHIPS * (right.prob/N_CHIPS) + self.twos/N_CHIPS *1 + (1 - self.ones/N_CHIPS - self.twos/N_CHIPS)*(left.prob/N_CHIPS); * N_CHIPS
    // src_ptr[0] = self.ones * (right.prob) + self.twos *1/N_CHIPS + (1 - self.ones - self.twos)*(left.prob); / N_CHIPS    

    self.ones = n_defects;
    self.twos = 0;
    self.zeros = N_CHIPS - n_defects;

    int left_idx = 0;

    while(self.ones >= 0){
        #ifdef VERBOSE
        printf("(%d, %d, %d)\t", self.zeros, self.ones, self.twos);
        #endif
        // Find right/left
        left.ones = self.ones + 1;
        left.twos = self.twos;
        left.zeros = N_CHIPS - left.ones - left.twos;
        left.prob = arr[left_idx];

        //passert(self.ones >= 1, "Tring to find right node but cant");
        right.ones = self.ones - 1;
        right.twos = self.twos + 1;
        right.zeros = N_CHIPS - right.ones - right.twos;
        right.prob = arr[left_idx + 1];

        // Compute self.prob
        //self.prob = self.ones*right.prob +  self.zeros*left.prob + self.twos*N_CHIPS**div_factor;
        //self.prob = self.ones*right.prob +  self.zeros*left.prob + self.twos*prob->div_factor;
        //self.prob = self.ones/N_CHIPS * right.prob/div_factor + self.zeros/N_CHIPS * left.prob/div_factor + self.twos/N_CHIPS
        self.prob = (self.ones*right.prob + self.zeros*left.prob + self.twos)/N_CHIPS;
        // self.prob (real) = self.ones/N_CHIPS * right.prob/div_factor + self.zeros/N_CHIPS * left.prob/div_factor + self.twos/N_CHIPS
        // self.prob (real) = (self.ones * right.prob + self.zeros * left.prob + self.twos*div_factor) / (div_factor*N_CHIPS)

        arr[left_idx] = self.prob;

        left_idx += 1;
        self.ones -= 2;
        self.twos += 1;
        self.zeros += 1;
    }
    #ifdef VERBOSE
    printf("\n");
    #endif

    //prob->div_factor = prob->div_factor*N_CHIPS;

}



double compute_prob(){
    // Init structure

    probabilities_t prob = {0};


    #ifdef VERBOSE
    print_tree(prob.arr, prob.div_factor, N_DEFECTS);
    #endif

    for(int i = N_DEFECTS - 1; i >= 0; i -= 1){
        compute_n_minus_1(&prob, i);
        #ifdef VERBOSE
        print_tree(prob.arr, prob.div_factor, i); // N/2 + 1
        #endif
    }

    // 
    //double top = (double) prob.arr[0];
    //double divide_factor = (double)prob.div_factor;

    //printf("top = %ld/%f, bot = %f\n", prob.arr[0], top, prob.div_factor);


    return prob.arr[0];
}




int main(){



    printf("Probability of a chip having 3+ defects for %d chips, %d defects = %.12f\n", N_CHIPS, N_DEFECTS, compute_prob() );


}