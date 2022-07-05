/*A pretty common way of coding fizzbuzz using for loops and else if statements*/
#include<iostream>

int main(void) {
    for(int i = 1; i < 101; i++) {
        if(i % 3 == 0 && i % 5 == 0) {
            std::cout<<"FizzBuzz\n";
        }
        else if(i % 3 == 0) {
            std::cout<<"Fizz\n";
        }
        else if(i % 5 == 0) {
            std::cout<<"Buzz\n";
        }
        else {
            std::cout<<i<<'\n';
        }
    }

    return 0;
}