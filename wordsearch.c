#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;
int* row; //x-coord
int* col; //y-coord
int* warning;
char** num_arr;
// Main function, DO NOT MODIFY 
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;
    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }
    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));
    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);
    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

int distance(int i, int j, int x, int y){
    if (i == x){
        if (((j - y) == 1) || ((j-y) == -1)){
            return 0;
            //0 means true;
        }
        return 1;
    }
    else if (j == y){
        if (((i - x) == 1) || ((i-x) == -1)){
            return 0;
        }
        return 1;
    }
    else{
        int d = (i - x) * (i - x);
        d = d + ((j - y) * (j - y));
        if (d == 2){
            return 0;
        }
        else {
            return 1;
        }
    }
}

int recursive(int x, int y, int k, char** arr, char* word){
    int i, j;
    // k = 1 bc first letter found
    static int count;

    warning = (int*)malloc(20 * sizeof(int));

    printf("%d", *(row));
    printf("%d", *(col));


    for (i = 0; i < bSize; i++){
        for (j = 0; j < bSize; j++){   //j++ not i++
            if ((*(*(arr + i) + j) == (*(word + k))) && (distance(x, y, i, j) == 0)){
                if ((i != *(warning)) && (j != *(warning+1))){
                    *(row + k) = i;
                    *(col + k) = j;
                    printf("%d", i);
                    printf("%d", j);
                    printf("%c", *(*(arr + i) + j));
                    printf("%c", *(word + k));
                    k++;
                    return recursive(i, j, k, arr, word);
                }
            }
            if (k == strlen(word)){ //use strlen not len
                return 0; //done now
            }
        }
    }
    count = 0;
    if (k < strlen(word)){
        count++;
        *(warning) = *(row);
        *(warning + 1) = *(col);
        x = *(row);
        y = *(col);
        memset(row, 0, k * sizeof(int));
        memset(col, 0, k * sizeof(int));
        *(row) = x;
        *(col) = y;
        return recursive(x, y, 1, arr, word);
    }
    return 0;
}

void convert(int* horizontal, int* vertical, char* word){
    int j = 1; //
    for (int i = 0; i < strlen(word); i++){
        (*(*(num_arr + (*(horizontal + i))) + (*(vertical + i)))) = (char)(i + 1 + '0');
    }
}

void printPuzzle(char** arr) {
// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    int i, j;
    for(i = 0; i < bSize; i++) {
        for (j = 0; j < bSize - 1; ++j) {
            printf("%c",*(*(arr + i) + j));
            //printing character so use %c 
            printf(" ");         
        }
        printf("%c", *(*(arr + i) + j));
        printf("\n");
    }
}
void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...
    int i, j;
    int count = 0;
    num_arr = (char**)malloc(bSize * sizeof(char*));
    //already declared num_arr as global
    for(i = 0; i < bSize; i++) {
        *(num_arr + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            *(*(num_arr + i) + j) = '0';         
        }
        *(*(num_arr + i) + j) = '0'; 
    }

    printf("\nPrinting the search path:\n");
    printPuzzle(num_arr);

    row = (int*)malloc(strlen(word) * sizeof(int)); //x-coord
    col = (int*)malloc(strlen(word) * sizeof(int));//y-coord
    //to make these print/not have seg fault, malloc them

    for(i = 0; i < bSize; i++) {
        for (j = 0; j < bSize; j++) {
            if ((*(*(arr + i) + j) == *(word + 0)) && (count == 0)){
                *(row + count) = i;
                *(col + count) = j;
                printf("%d \n", *(row + count));
                printf("%d \n", *(col + count));
                count++;
                recursive(i, j, 1, arr, word);
            }        
        }  
    }

    //convert(horizontal, vertical, word);

    //best order
    //new first letter
    //duplicate 
    //turn into num_array 
    //all caps

}
