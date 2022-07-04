/* 
    AUTHOR: KEVIN PLUAS
    A small C program showing off a couple algorithms from CLRS. 

    This program starts by generating an array of 100 random ints completely unsorted
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define length 100  //size of the array

typedef struct Node Node;
struct Node {
    int value;
    Node* next;
};

void printll(Node* list);


//prototypes
int* generate_array1000(void);
void print_array1000(int* array);

void binary_search(int* array, int value);
void insertion(int* arrptr, int mode);
void print_array(int* array);
int* generate_array(void);
void linear_search(int* array, int value);
void binary_adder(int x, int y, int bits);
int expo(int base, unsigned int power);
void linkedlist(int* array);

void print_menu(void) {
    printf("Select your function\n");
    printf("1. Insertion Sort (nondecreasing)\n");
    printf("2. Insertion Sort (nonincreasing)\n");
    printf("3. Linear Search\n");
    printf("4. Binary Adder\n");
    printf("5. Linked List Creation/Printing\n");
    printf("6. Create and print out 1000 random numbers in an array\n");
    printf("\tWarning! Could be slow!\n");
    printf("7. Binary Search\n");
}

int main(void) {
    int *arrptr = generate_array(); //a pointer to the array 
    print_array(arrptr);           //iterate and display the 100 numbers

    int choice, value;

    while(1) {
        print_menu(); //display the menu for the user
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                insertion(arrptr, 1);
                printf("Using insertion sort: \n");
                print_array(arrptr);
                break;
            case 2:
                insertion(arrptr, 2);
                printf("Using insertion sort (nonincreasing):\n");
                print_array(arrptr);
                break;
            case 3:
                printf("Enter a value to search for: ");
                scanf("%d", &value);
                linear_search(arrptr, value);
                break;
            case 4:
                int x, y, bits;
                printf("Enter the 1st binary number: ");
                scanf("%d", &x);
                printf("Enter the 2nd binary number: ");
                scanf("%d", &y);
                printf("How many bits will the resulting array need to store? ");
                scanf("%d", &bits);
                binary_adder(x, y, bits);
                break;
            case 5:
                linkedlist(arrptr);
                break;
            case 6:
                arrptr = generate_array1000();
                print_array1000(arrptr);
                break;
            case 7:
                printf("Type the number you wish to search for: ");
                scanf("%d", &value);
                binary_search(arrptr, value);
                break;
            default:
                return 0;
            
        }
    }
    return 0;
}

//return a pointer to an array of 100 randomly generated ints for use in the following sorting algorithms
int* generate_array(void) {
    static int array[length];

    time_t t;

    //generate the seed for rand()
    srand((unsigned) time(&t));

    for(int i = 0; i < 100; i++) {
        array[i] = (rand() % 101);
    }

    return array;
}

//receives a value as input and output the index of where the value was found if it exists
void binary_search(int* array, int value) {
    int low = 0;
    int high = length - 1;

    while(low <= high) {
        int mid = (low + high) / 2;

        if(value == *(array + mid)) {
            printf("Found at index %d\n", mid);
            return;
        }
        else if(value < *(array + mid)) {
            high = mid - 1;
        }
        else {
            low = mid + 1;
        }
    }

    printf("Value not found\n");
    return;
}

void print_array1000(int* array) {
    printf("Current 1000 Array:\n");
    for (int i = 0; i < 1000; i++)
    {
        printf("Array [%d] at address %p: %d\n", i, (void*)(&array+i), *(array+i));
    }
    
}

//prints the array & the memory address of each index
void print_array(int* array) {
    printf("Current Array:\n");
    for(int i = 0; i < length; i++) {
        printf("array[%d]: %d at address %p\n", i, *(array + i), (void*)(&array+i));
    }
}

//mode determines the order in which the numbers are arranged
//1 - nondecreasing
//2 - nonincreasing
void insertion(int* arrptr, int mode) {
    int key, i;

    if(mode == 1) {
        for(int j = 1; j < length; j++) { //the loop needs to start at the second index
            key = *(arrptr + j); //assign the int to a temp variable 
            i = j - 1;
            while(i >= 0 && *(arrptr + i) > key) { //if the previous number is larger than the next number ...
                *(arrptr + (i + 1)) = *(arrptr + i); //swap them
                i -= 1;
            }
            *(arrptr + (i + 1)) = key;
        }
    }

    if(mode == 2) {
        printf("Sorting in decreasing order:");
        for(int j = 1; j < length; j++) {
            key = *(arrptr + j); //the number currently being sorted | starts at array[98] | last number is at array[99]
            i = j - 1;          //compare the number to array[99]
            while(i >= 0 && *(arrptr + i) < key) { //if the key is greater than the next number
                *(arrptr + (i + 1)) = *(arrptr + i);
                i -= 1;
            }
            *(arrptr + (i + 1)) = key;
        }
    }
}

//uses linear search to find the first instance of a value and outputs the index 
void linear_search(int* array, int value) {
    for(int i = 0; i < length; i++) {
        if(value == *(array + i)) {
            printf("%d found at index %d\n", value, i);
            return;
        }
    }
    printf("Value not found!\n");
}

//inputs 2 binary numbers and outputs the sum of the numbers in binary stored in 
//an array. Bits is used to determine the size of the resulting array
void binary_adder(int x, int y, int bits) {
    int operand = bits - 1; //length of operand array

    //first, store the operands into their respective arrays
    int a[operand], b[operand], sum[bits];


    //The binary numbers are stored with the least significant bit in the 1st index
    //example , 1010 = 10
    for(int i = 0; i < operand; i++) { //place the bits in reverse for easier adding
        a[i] = x % 10; b[i] = y % 10;
        x /= 10; y /= 10;
    }

    //now add the numbers TRY IT BEFORE RESORTING TO THE ANSWER KEVIN!!!
    for(int i = 0; i < operand; i++) { //go thru each of the indexes
        sum[i] = a[i] + b[i];
    }
    // //output the current binary array
    // for(int i = 0; i < operand; i++) {
    //     printf("%d ", a[i]);
    // }

    // printf("\n");

    // for(int i = 0; i < operand; i++) {
    //     printf("%d ", b[i]);
    // }

}

//raises the base by an inputted power and returns the result
int expo(int base, unsigned int power) {
    if(power == 0) {
        return 1;
    }
    int result = 1;

    for(int i = 0; i != power; i++) {
        result *= base;
    }
    return result;
}

//generates 1000 randomly generated numbers for an array
int* generate_array1000(void) {
    static int array[1000];

    time_t t;

    //generate the seed for rand()
    srand((unsigned) time(&t));

    for(int i = 0; i < 1000; i++) {
        array[i] = (rand() % 1001);
    }

    return array;
}

//generates a linked list using the generated array
void linkedlist(int* array) {
    Node* head = NULL;
    Node* current;
    head = (Node*) malloc(sizeof(Node));
    current = head; //Current will point to the unchanging head node
    if(head == NULL) {
        printf("Not enough memory\n");
        return; //exit function if not enough memory to create the head
    }

    for(int i = 0; i < length+1; i++) {
        current->next = (Node*) malloc(sizeof(Node));
        current = current->next;
        current->value = *(array+i);
    }
    //at the end of the loop, set next to NULL to classify it

    current->next = NULL;

    printf("Linked list successfully created!\n");

    printll(head);
}

//prints the contents of the linked list
void printll(Node* list) {
    for(int i = 0; list->next != NULL; i++) {
        printf("Linked List node #%d: %d at address %p\n", i, list->value, 
        (void*)(&list->value));
        list = list->next;
    }
}