#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


#include "words.h"
// Largest palindrom in above file i INTRODUCE (9 chars)


void passert(bool cond, char *msg){
    if(!cond){
        printf("%s", msg);
        exit(1);
    }
}



int nsquares = 31622;
uint32_t squares[31622 + 1]; // squares[i] = i**2
uint32_t digits_indxs[9 + 2];

void find_squares(){
    digits_indxs[0] = 0;
    digits_indxs[1] = 1;
    digits_indxs[10] = 31623;

    int i = 1;
    int i_squared = 1;
    int n_digits_next = 2;
    int n_digits_roof = 10;

    while(i < 31623){

        squares[i] = i_squared;
        if(i_squared >= n_digits_roof){
            digits_indxs[n_digits_next++] = i;
            n_digits_roof = n_digits_roof*10;
        }


        //i = i + 1;
        //i_squared = i*i;
        // (i + 1)**2 = i**2 + 2*i + 1
        i_squared = i_squared + (i << 1) + 1;
        i += 1;
    }

    for(int i = 0; i < 10; i+= 1){
        printf("%d digits, %d / %d\n", i, squares[digits_indxs[i]], digits_indxs[i]);
    }
}




static char buffer[256];

bool ispalindrome(char *word, char *otherword)
{
    int wordlen = strlen(word);

    if(wordlen != strlen(otherword)){
        return false;
    }

    strcpy(buffer, otherword);

    for(int j = 0; j < wordlen; j += 1)
    {
        char target = word[j];
        //printf("Target = %c\n", target);

        for(int i = 0; i <= wordlen; i += 1)
        {
            if(buffer[i] == target){
                buffer[i] = 1;
                break;
            }
            else if(buffer[i] == 0)
            {
                return false;
            }
        }
        //printf("%s\n", buffer);

    }
    return true;
}




typedef struct mapping{
    uint8_t tonum[26]; // A - Z
} mapping_t;

// Return the LSB of num, update num to be 1 digit shorter
uint8_t lsb(uint32_t *num){
    passert(*num != 0, "Error, trying to get the LSB of 0 value");

    uint32_t temp = *num % 10;
    *num = (uint32_t)((*num - temp)/10);

    
    return temp;
}

bool create_map(mapping_t *map, char *a, uint32_t num, int n){
    // reset map
    memset(map->tonum, 10, 26);

    uint32_t oldnum = num;

    // a has n letters, num has n digits
    passert(n >= 0 && n <= 9, "Creating bad map");

    for(int j = n - 1; j >= 0; j -= 1){
        if(j == 0){
            passert(num > 0 && num < 10, "Bad number used for mapping");
        }

        int letternum = a[j] - 'A';
        uint8_t value = lsb(&num);

        if(map->tonum[letternum] < 10 && map->tonum[letternum] != value){ // Mapping for this letter already created
            return false;
        }
        // Mapping to this number already exists, and its not for current letter
        for(int q = 0; q < 26; q += 1){
            if(map->tonum[q] == value && q != letternum){
                return false;
            }
        }

        map->tonum[letternum] = value;
    }

    return true;
}



int compare_uint32(const void *a, const void *b) {
    uint32_t arg1 = *(const uint32_t *)a;
    uint32_t arg2 = *(const uint32_t *)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

uint32_t use_mapping(char *word, mapping_t map, int n){
    uint32_t value = 0;
    for(int i = 0; i < n; i += 1)
    {
        value = value*10;
        passert(map.tonum[word[i] - 'A'] < 10, "Using invalid maping for input word");

        uint8_t digit = map.tonum[word[i] - 'A'];
        value += digit;
    }
    return value;
}

bool check_mapping(char *word, mapping_t map, int n){
    // 1) Recover the number from the word

    // Check that the MSB != 0
    if(map.tonum[word[0] - 'A'] == 0){
        return false; // Bad non-fatal mapping
    }
    uint32_t value = use_mapping(word, map, n);

    // 2) Check that number is a squares& (i.e. is in squares) (do binary search)
    uint32_t *ptr = bsearch(&value, squares, nsquares, sizeof(uint32_t), compare_uint32);

    if(ptr == NULL){
        return false; // number is not a square
    }

    passert(*ptr == value, "Failed bsearch");

    return true;
}

uint32_t is_square_palindrome(char *a, char *b){

    if(!ispalindrome(a, b)){return false;}

    int length = strlen(a);
    passert(length <= 9, "Length of palindrome is too big\n");
    // First need to see what combinations of numbers 0-9 can create a square
    // 1-9

    // for each square with n digits
    // 1) Try to make a mapping to src word.
    // 2) redo the mapping to the other word.
    // 3) Check if that is a square


    int i;
    int i_squared;
    mapping_t map;

    uint32_t mapped_value = 0;


    for(int i = digits_indxs[length]; i < digits_indxs[length + 1]; i += 1)
    {
        i_squared = squares[i]; //i , i**2

        // Map to source word;
        //printf("Creating map for %s\n", a);
        if(!create_map(&map, a, i_squared, length) ){
            continue;
        }
        if(!check_mapping(b, map, length) ){
            continue;
        }

        // Keep the largest value for this palindrom pair
        uint32_t valuea = use_mapping(a, map, length);
        uint32_t valueb = use_mapping(b, map, length);

        
        printf("Found a match %d, %d\n", valuea, valueb);


        if(valuea > mapped_value){
            mapped_value = valuea;
        }
        if(valueb > mapped_value){
            mapped_value = valueb;
        }

    }

    return mapped_value;


}


char *find_largest_palindrome(){

    int largest_length = 0;
    char *best_word = NULL;

    // For each source word
    for(int i = 0; i < nwords; i += 1)
    {
        char *base_word = words[i];

        if(strlen(base_word) <= largest_length){
            continue;
        }

        // Compare against other words to find if its a palindrome
        for(int j = i + 1; j < nwords; j += 1)
        {
            char *other_word = words[j];
            if(ispalindrome(base_word, other_word)){
                largest_length = strlen(base_word);
                best_word = base_word;
            }

        }

    }
    return best_word;

}

int main(){

    char *word;

    word = find_largest_palindrome();
    find_squares();

    //printf("Is Palindrome = %d\n", ispalindrome("ADMINISTRATION", "CHARACTERISTIC") );
    //return;
    printf("Largest palindrome = %s (%d)\n", word, strlen(word));


    int check_size = 5;
    for(int j = 0; j < nwords; j += 1){
        if(strlen(words[j]) != check_size){ continue; }


        for(int i = 0; i < nwords; i += 1)
        {
            if(j == i){ continue; }

            if(ispalindrome(words[j], words[i])){
                printf("9 letter word = %s\n", words[j]);
                printf("    : %s, is_square = %d\n", words[i], is_square_palindrome(words[j], words[i]));
            }
        }
    }

}

//CREATION, REACTION

// 81450625

// BOARD, BROAD
// 18769  16879
//        18769
// 17689