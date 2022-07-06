/*Accepts a string from standard input and outputs the number of occurances of a character using maps and iterators*/
#include<iostream>
#include<map>

int main(int argc, const char** argv) {
    std::string input;
    if(argc == 2) {
        input = *(argv+1);
    }
    else {
        std::getline(std::cin, input);
    }

    std::map<char, int> charOccs;

    for(int i = 0; i < input.size(); i++) {
        if(charOccs.count(input[i] < 1)) {  /*If no unique key exists for this char, create one*/
            charOccs.insert(std::pair<char, int>(input[i], 1)); 
        }
        else {
            charOccs[input[i]]++; /*We saw another of this nonunique char, increment by 1*/
        }
    }

    for(auto it = charOccs.begin(); it != charOccs.end(); ++it) {
        std::cout<< it->first << "\t" << it->second << '\n';
    }
}