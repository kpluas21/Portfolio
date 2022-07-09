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

char encrypt(const std::string&, char, char, char);
char decrypt(const std::string&, char, char, char);

int main(int argc, char* argv[]) {
    // if(argc < 3 || argc > 4) {
    //     std::cerr<<"Usage: affine [(e)ncrypt/(d)ecrypt] [a key] [b key] [filename]\n";
    //     std::cerr<<"\taffine [--help]\n";
    //     return 1;
    // }

    // std::string str = argv[1]; /*e for encrypt. d for decrypt*/


    const std::string alphabet {"abcdefghijklmnopqrstuvwxyz"};        /*We will use the index of the string for our formulas. A = 0, ..., Z = 25*/
    std::string input, result = "";                                   /*The text to be encrypted/decrypted and subsequently outputted*/
    int a, b, m = 26;

    std::cout<<"Please input your text:\n";
    std::getline(std::cin, input);

    do {
        std::cout<<"Please enter your encryption keys in the form a b\n";
        std::cin>>a>>b;

        if(!std::cin) {                     /*If the user puts a letter, clear and empty the stream. Try again.*/
            std::cout<<"Invalid input\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while ( (b < 0 || b > 25) || (std::gcd(a, 26) != 1) ); /*Prompt the user to input the keys again if they aren't valid*/

    for(auto c : input) {
        if(isalpha(c)) {
            std::cout<<encrypt(alphabet, c, a, b);
        }
        else {
            std::cout<<c;
        }
    }
}

/*Encrypts and returns a single letter with its respective casing.*/
char encrypt(const std::string& alphabet, char c, char a, char b) {
    char encryptLetter = alphabet[((((static_cast<int>(c) % 32) - 1) * a) + b) % 26];
    
    if(isupper(c)) { return toupper(encryptLetter); }
    
    return encryptLetter;
}

char decrypt(const std::string& alphabet, char c, char a, char b) {

}