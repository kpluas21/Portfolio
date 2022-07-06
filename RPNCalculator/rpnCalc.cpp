/*My implementation of an RPN style calculator in C++*/
/*AUTHOR : KEVIN PLUAS*/

/*It works by accepting a string as input. The string is then parsed for number and operator tokens. Afterwards it evaluates the expression.*/

#include<iostream>
#include<string>
#include<sstream>
#include<cstring>
#include<vector>
#include<algorithm>

enum Operations {
    ADD,
    SUB,
    MUL,
    DIV,
    ERR,
};

/*PROTOTYPES*/
bool isNumber(std::string);
Operations parseOperation(std::string);
int evaluate(std::vector<int>&, Operations);

int main(int argc, const char** argv) {
    // std::stack<int> operands;
    std::vector<int> operands;
    int num;
    std::string input;
    std::string token;
    

    while(true) {
        std::cout<<"> ";                        /*Display the prompt*/
        std::getline(std::cin, input);          /*Grab everything the user inputs until the newline*/

        std::istringstream ss(input);           /*Create an input stream out of input*/

        while(std::getline(ss, token, ' ')) {   /*Parse through the stream and tokenize each thing before any whitespace*/
            if(isNumber(token)) {
                operands.push_back(std::stoi(token));/*Tokenize each thing until it reaches the first thing that isnt a number*/
            }
            else {
                std::cout<<evaluate(operands, parseOperation(token))<<'\n';
                operands.clear();
            }
        }
    }
}

/*Returns true if the string token was a number. False otherwise*/
bool isNumber(std::string token) {
    for(char c : token) {
        if(isdigit(c) == 0) {   /*This works by checking each char in the token and returns false one the first nondigit it finds*/
            return false;
        }
    }
    return true;
}

/*Attempts to figure out what the token is. Returns INVALID if it can't be done*/
/*Currently implemented operations are Adding, sub, multi, div*/
Operations parseOperation(std::string token) {
    if(std::strcmp(token.c_str(), "+") == 0) {
        return ADD;
    }
    if(std::strcmp(token.c_str(), "-") == 0) {
        return SUB;
    }
    if(std::strcmp(token.c_str(), "*") == 0) {
        return MUL;
    }
    if(std::strcmp(token.c_str(), "/") == 0) {
        return DIV;
    }
    
    return ERR;
}

int evaluate(std::vector<int>& operands, Operations oper) {
    int result = 0;
    std::vector<int>::iterator it; 
    bool hasZero;

    switch(oper) {
        case ADD:
            for(it = operands.begin(); it != operands.end(); it++) {
                result += *it;
            }
            break;
        case SUB:
            for(it = operands.begin(); it != operands.end(); it++) {
                result -= *it;
            }
            break;
        case MUL:
            result = 1;
            for(it = operands.begin(); it != operands.end(); it++) {
                result *= *it;
            }
            break;
        case DIV: /*We first need to see if there are any zeros past the 1st index of the vector. Return an error if this is true*/
            result = 1;
            hasZero = (std::find(operands.begin() + 1, operands.end(), 0)) != operands.end(); 
            if(hasZero) {
                std::cout<<"Divide by zero error\n";
                return -1;
            }
            else {
                for(it = operands.begin(); it != operands.end(); it++) {
                result /= *it;
                }
            }
            break;
        default:
            std::cout<<"Invalid operator entered\n";
            return -1;
    }

    return result;
}