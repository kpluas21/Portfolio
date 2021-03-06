/*A ROT13 cipher program. It simply shifts each letter by 13 places, so running this program on a piece of text twice will restore the original text*/
/* Essentially a modified Ceaser cipher */
/* AUTHOR : KEVIN PLUAS */

#include<iostream>
#include<vector>

int main(int argc, char* argv[]) {
    const std::string alphabet {"abcdefghijklmnopqrstuvwxyz"};

    for(std::string input; std::getline(std::cin, input);) {
        for(auto c : input) {
            if(isalpha(c)) {
                std::cout << alphabet[(((static_cast<int>(c) % 32 - 1) + 13 ) % 26)];
            }
            else {
                std::cout<<c;
            }
        }
    }

    return 0;
}