/*Affine Cipher*/
/*AUTHOR: KEVIN PLUAS*/
/*Allows some text to either be encrypted or decrypted. Accepts std::cout or a text file as input. Outputs either the encrypted or decrypted text*/
/*At minimum, the program requires the mode, and the two valid keys to operate. If a text file is specififed it will use that instead*/
/*of std::cout*/

#include<iostream>
#include<vector>
#include<numeric>
#include<limits>
#include<fstream>

char encrypt(const std::string&, char, int, int);
char decrypt(const std::string&, char, int, int);
int findInverse(int);

int main(int argc, char* argv[]) {
    // if(argc < 3 || argc > 4) {
    //     std::cerr<<"Usage: affine [(e)ncrypt/(d)ecrypt] [a key] [b key] [filename]\n";
    //     std::cerr<<"\taffine [--help]\n";
    //     return 1;
    // }

    std::string mode;
    if(argc == 2) {
        mode = argv[1];
    }

    const std::string alphabet {"abcdefghijklmnopqrstuvwxyz"};        /*We will use the index of the string for our formulas. A = 0, ..., Z = 25*/
    std::string input, result = "";                                   /*The text to be encrypted/decrypted and subsequently outputted*/
    int a, b, m = 26;

    std::cout<<"Please input your text:\n";
    std::getline(std::cin, input);

    do {
        std::cout<<"Please enter your keys in the form a b\n";
        std::cin>>a>>b;

        if(!std::cin) {                     /*If the user puts a letter, clear and empty the stream. Try again.*/
            std::cout<<"Invalid input\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while ( (b < 0 || b > 25) || (std::gcd(a, 26) != 1) ); /*Prompt the user to input the keys again if they aren't valid*/

    if(mode == "e") {
        for(auto c : input) {
            if(isalpha(c)) {
                std::cout<<encrypt(alphabet, c, a, b);
            }
            else {
                std::cout<<c;
            }
        }
        return 0;
    }

    else if(mode == "d") {
        //calculate the inverse only once. Mod is an expensive operation
        int inverse = findInverse(a);
        std::cout<<"Modular inverse of " << a << " is " << inverse<<'\n';
        for(auto c : input) {
            if(isalpha(c)) {
                std::cout<<decrypt(alphabet, c, inverse, b);
            }
            else {
                std::cout<<c;
            }
        }
        return 0;
    }
    std::cout<<"Invalid mode\n";
    return 1;
}

/*Encrypts and returns a single letter with correct capitalization.*/
char encrypt(const std::string& alphabet, char c, int a, int b) {
    int chIndex = (static_cast<int>(c) % 32) - 1; //This is what converts our letters into a integer ranging from 0 - 25

    char encryptLetter = alphabet[((chIndex * a) + b) % 26];
    
    if(isupper(c)) { return toupper(encryptLetter); }
    
    return encryptLetter;
}

/*Decrypts and returns a single letter with correct capitalization*/
/*A little more complicated than I once thought, this requires calculating the modular inverse to figure out A^-1*/
char decrypt(const std::string& alphabet, char c, int inverse, int b) {

    int chIndex = (static_cast<int>(c) % 32) - 1;
    char decryptLetter = alphabet[inverse * (chIndex - b) % 26];

    if(isupper(c)) { return toupper(decryptLetter); }

    return decryptLetter;
}

//Calculates the modular inverse given a modulo of 26. a MUST be coprime with 26 in order for this to work
int findInverse(int a) {
    int inverse = 0;
    
    for(int i = 0; i < 26; i++) {
        /*Since the modulo is small, we do a quick search to find the inverse. (a * i ) % 26*/
        if( ( ( (a * i) % 26 ) == 1 ) ) {
            inverse = i;
        } 
    }
    return inverse;
}