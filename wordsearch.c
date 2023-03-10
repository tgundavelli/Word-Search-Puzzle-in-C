#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int c;
int bSize;
int* row; //x-coord
int* col; //y-coord
int* x_warn;
int* y_warn;
int* warning;
char* duplicates;
char* repeats;
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

char* hardcode(char* word){
    //library function to convert uppercase/lowercase not allowed
    for (int i = 0; i < strlen(word); i++){
        if ((*(word + i)) == 'a'){
            *(word + i) = 'A';
        }
        else if ((*(word + i)) == 'b'){
            *(word + i) = 'B';
        }
        else if ((*(word + i)) == 'c'){
            *(word + i) = 'C';
        }
        else if ((*(word + i)) == 'd'){
            *(word + i) = 'D';
        }
        else if ((*(word + i)) == 'e'){
            *(word + i) = 'E';
        }
        else if ((*(word + i)) == 'f'){
            *(word + i) = 'F';
        }
        else if ((*(word + i)) == 'g'){
            *(word + i) = 'G';
        }
        else if ((*(word + i)) == 'h'){
            *(word + i) = 'H';
        }
        else if ((*(word + i)) == 'i'){
            *(word + i) = 'I';
        }
        else if ((*(word + i)) == 'j'){
            *(word + i) = 'J';
        }
        else if ((*(word + i)) == 'k'){
            *(word + i) = 'K';
        }
        else if ((*(word + i)) == 'l'){
            *(word + i) = 'L';
        }
        else if ((*(word + i)) == 'm'){
            *(word + i) = 'M';
        }
        else if ((*(word + i)) == 'n'){
            *(word + i) = 'N';
        }
        else if ((*(word + i)) == 'o'){
            *(word + i) = 'O';
        }
        else if ((*(word + i)) == 'p'){
            *(word + i) = 'P';
        }
        else if ((*(word + i)) == 'q'){
            *(word + i) = 'Q';
        }
        else if ((*(word + i)) == 'r'){
            *(word + i) = 'R';
        }
        else if ((*(word + i)) == 's'){
            *(word + i) = 'S';
        }
        else if ((*(word + i)) == 't'){
            *(word + i) = 'T';
        }
        else if ((*(word + i)) == 'u'){
            *(word + i) = 'U';
        }
        else if ((*(word + i)) == 'v'){
            *(word + i) = 'V';
        }
        else if ((*(word + i)) == 'w'){
            *(word + i) = 'W';
        }
        else if ((*(word + i)) == 'y'){
            *(word + i) = 'Y';
        }
        else if ((*(word + i)) == 'z') {
            *(word + i) = 'Z';
            //keep as else if instead of else bc else is for uppercase letters
        }
    }

    return word;
}

int distance(int i, int j, int x, int y){
    //(i == x) and (j == y) not allowed
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
    int ban;

    //printf("Start %d %d \n", x, y);

    // k = 1 bc first letter found
    //static does not get initialized everytime
    //but if called outside of recursive function for change in first letter,
    //problem arises

    //next time maybe have less local variables that have the same name
    for (i = 0; i < bSize; i++){
        for (j = 0; j < bSize; j++){   //j++ not i++
            //printf("Test %d %d \n", i, j);
            if ((*(*(arr + i) + j) == (*(word + k))) && (distance(x, y, i, j) == 0)){
                if (c == 0){
                    //printf("IF %d %d \n", i, j);
                    *(row + k) = i;
                    *(col + k) = j;
                    k++;
                    return recursive(i, j, k, arr, word);
                } else {
                for (ban = 0; ban < c; ban++){
                    if ((i != *(x_warn + ban)) || (j != *(y_warn + ban))){ //and in coding is different from and in truth tables
                        //printf("ELSE %d %d \n", i, j);
                        *(row + k) = i;
                        *(col + k) = j;
                        k++;
                        if (k == (strlen(word))){ //use strlen not len
                            return 0; //done now, use len, ask before recursion
                        } 
                        return recursive(i, j, k, arr, word);
                    }
                }
                }
            }
        }
    }


    if (k < strlen(word)){
        *(x_warn + c) = *(row + 1); //store x and y-coord in 2 arrays instead of one like row and col
        *(y_warn + c) = *(col + 1);
        //printf("HERE %d %d %d \n",c, *(x_warn + c) , *(y_warn + c));
        c++;
        //for now
        x = *(row);
        y = *(col);
        if (c == 6){ //3 above first letter, 3 below, 2 to the sides
            memset(row, -1, k * sizeof(int)); //only focus on first coord to check if wrong
            //printf("This is it\n");
            return 0; //cannot be found, returning 1 doesn't end function
            //change row numbers to -1 to show smth is wrong
        }
        else {
            //printf("END %d %d %d \n", c, x, y);
            memset(row, 0, k * sizeof(int));
            memset(col, 0, k * sizeof(int));
            *(row) = x;
            *(col) = y;
            return recursive(x, y, 1, arr, word);
        }
    }
    return 0;
}

void convert(int* horizontal, int* vertical, char* word){
    //check for repeats, count number of duplicates
    //you cannot sort array because it is coordinates x and y

    duplicates = (char*)malloc(20 * sizeof(char));
    repeats = (char*)malloc(20 * sizeof(char));
    //this is an array and char* means strings so a character array
    //cannot contain more than one character in one index
    memset(duplicates, '0', 20 * sizeof(int));

    //first check for frequency
    int prev = -1;
    int next = 0;

    for (int a = 0; a < strlen(word); a++){
        if (next == strlen(word)){ //0..wordlen is 1..wordlen-1
            break;
            }
        if (next != prev){
            *(duplicates + next) = (char)(a + 1 + '0');
        }
        else {
            a++;
            *(duplicates + next) = (char)(a + 1 + '0');
        }  
        for (int b = 0; b < strlen(word); b++){
            if ((a != b) && ((*(horizontal + a)) == (*(horizontal + b))) && ((*(vertical + a)) == (*(vertical + b)))){
                next++;
                *(duplicates + next) = (char)(b + 1 +'0');
                prev = b + 1;
            }
        }
        next++;
    }

    //then somehow print it
    //how to know if it's a repeating coordinate
    //i created the output but not how to check to plug it in
    //problem is characters can only be one character. you need to combine properly
    //just because two diff nums are next to each other, doesn't mean they're together

    for (int i = 0; i < strlen(word); i++){
        (*(*(num_arr + (*(horizontal + i))) + (*(vertical + i)))) = (char)(i + 1 + '0');
    }
}

void mash(){
    //when there are duplicates
    //duplicates can't be stored in the char array
    
}

void printPuzzle(char** arr) {
// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    int i, j, k, m;
    int next = 0;
    int count = 0;
    int second = 0;
    
    for(i = 0; i < bSize; i++) {
        for (j = 0; j < bSize - 1; ++j) {
            printf("%c",*(*(arr + i) + j));
            //printing character so use %c 
            if (arr == num_arr){
                if (*(*(arr + i) + j) != '0'){
                    count++;
                    *(repeats + next) = *(*(arr + i) + j); //make sure right = left not left = right
                    next++;
                    for (k = 0; k < bSize; k++){
                        if ((*(duplicates + k)) == *(*(arr + i) + j)){
                            while (((*(duplicates + k - 1)) != ((*(duplicates + k)) - 1)) && ((k - 1) != -1) && (count >= 0)){
                                for (m = 0; m < next; m++){
                                    if (*(duplicates + k - 1) == *(repeats + m)){
                                        count = -1;
                                    }
                                }
                                if (count != -1){//while loop does not immediately terminate, only at beginning of iteration
                                    k--;
                                    count++;
                                    *(repeats + next) = *(duplicates + k);
                                    next++;
                                    printf("%c",*(duplicates + k));
                                    second++;
                                }
                            }
                        break; //to prevent infinity loop
                        //test
                        }
                    }
                }
                if (second > 0) {
                    for (int h = 0; h < (8 - second); h++){
                        printf(" ");
                    }
                    second = 0;
                }
                else {
                    printf("        "); 
                }
            }
            else {
                printf(" ");
            }        
        }
        printf("%c", *(*(arr + i) + j)); //for borders
        if (arr == num_arr){
                if (*(*(arr + i) + j) != '0'){
                    count++;
                    *(repeats + next) = *(*(arr + i) + j); //make sure right = left not left = right
                    next++;
                    for (k = 0; k < bSize; k++){
                        if ((*(duplicates + k)) == *(*(arr + i) + j)){
                            while (((*(duplicates + k - 1)) != ((*(duplicates + k)) - 1)) && ((k - 1) != -1) && (count >= 0)){
                                for (m = 0; m < next; m++){
                                    if (*(duplicates + k - 1) == *(repeats + m)){
                                        count = -1;
                                    }
                                }
                                if (count != -1){//while loop does not immediately terminate, only at beginning of iteration
                                    k--;
                                    count++;
                                    *(repeats + next) = *(duplicates + k);
                                    next++;
                                    printf("%c",*(duplicates + k));
                                }
                            }
                        break; //to prevent infinity loop
                        //test
                        }
                    }
                }
        }
        printf("\n"); //don't apply changed spacing here
    }

}
void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...
    int i, j;
    int a = 0;
    int b = 0;
    num_arr = (char**)malloc(bSize * sizeof(char*));
    //already declared num_arr as global
    for(i = 0; i < bSize; i++) {
        *(num_arr + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            *(*(num_arr + i) + j) = '0';         
        }
        *(*(num_arr + i) + j) = '0'; 
    }

    word = hardcode(word);

    warning = (int*)malloc(20 * sizeof(int)); 
    row = (int*)malloc(strlen(word) * sizeof(int)); //x-coord
    col = (int*)malloc(strlen(word) * sizeof(int));//y-coord
    //to make these print/not have seg fault, malloc them

    for(i = 0; i < bSize; i++) {
        for (j = 0; j < bSize; j++) {
            if (b == 0){
                if ((*(*(arr + i) + j) == *(word + 0)) && (a == 0)){
                    *(row) = i;
                    *(col) = j;
                    a++;
                    x_warn = (int*)malloc(20 * sizeof(int));
                    y_warn = (int*)malloc(20 * sizeof(int));
                    c = 0; 
                    recursive(i, j, 1, arr, word);
                    c = 0;
                    if (*(row) == -1){
                        *(warning + b) = i;
                        *(warning + b + 1) = j;
                        b++; //number of letters that don't work
                        a = 0; //if no end to word found, change to a different starting letter
                    }
                }
            } else {
                if ((*(*(arr + i) + j) == *(word + 0)) && (a == 0)){ //check if it both is not in warning and is fit
                    for (int d = 0; d < b; d+=2){
                        if ((i != *(warning + d)) || (j != *(warning + d + 1))){ 
                            *(row) = i;
                            *(col) = j;
                            a++;
                            c = 0;
                            recursive(i, j, 1, arr, word);
                            c = 0;
                            if (*(row + 1) == -1){
                                *(warning + b) = i;
                                *(warning + b + 1) = j;
                                b++; //number of letters that don't work
                                a = 0; //if no end to word found, change to a different starting letter
                            }    
                        }
                    }
                }
            }        
        }  
    } //make sure parathesis are symmetrical

    if (a != 0) {
        convert(row, col, word);
        printf("\nWord found!\n"); //\n at beginnning prints empty line above
        printf("Printing the search path:\n");
        printPuzzle(num_arr);
    }
    else {
        printf("\nWord not found!\n");
    }

    //duplicate or best order or new first letter
    //best order not doing well but let's focus on new first letter rn

    //best order due to first letter just not working
    //best order bc deadends. first letter not working is ultimate deadend
    //not able to go backwards

    //duplicate, no word found, multiple ways
    //one kinds of duplicates : 234 with 24 in same spot

}
