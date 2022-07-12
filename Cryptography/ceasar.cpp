/* A Ceasar cipher program. Accepts input from stdin, outputs to stdout */
/* AUTHOR: Kevin Pluas */

#include<iostream>
#include<vector>
#include<stdexcept>

int getChIndex(char);

int main(int argc, char** argv) {
    const std::string alphabet {"abcdefghijklmnopqrstuvwxyz"};
    std::string encyptedAlphabet {};

    if(argv[1] == nullptr) {
        std::cerr<<"Missing key\n";
        return 1;
    } 
    
    int key;
    try {
        key = std::stoi(argv[1]);
    }
    catch(const std::invalid_argument& e) {
        std::cerr << e.what() << " accepted an invalid argument\n";
        return 1;
    }
    
    std::cout<<key<<'\n';

    /* Here, we preemptively convert the letters using the key and store them in order for quick access.  */
    for(auto c : alphabet) {
        /* Shift the index according to the key , and use that as the new index for the encrypted letter */
        encyptedAlphabet.push_back(alphabet[(getChIndex(c) + key) % 26]);
    }



    for(std::string input; std::getline(std::cin, input);) {
        for(auto c : input) {
            if(isalpha(c)) {
                std::cout<< encyptedAlphabet[getChIndex(c) % 26];
            }
            else {
                std::cout<<c;
            }
        }
    }

    return 0;
}

/* Returns the numerical equivalent for a character. */
/* Sub 1 to bring it into the appropriate range [0 - 25] */
/* Example: A = 0, B = 2, ..., Z = 25 */
int getChIndex(char c) {
    return (static_cast<int>(c) % 32)- 1;
}