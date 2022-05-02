/*Randomly generates a password of at least length 16 using lowercase, uppercase, numbers and symbols*/
/* Author: Kevin Pluas */

#include<iostream>
#include<vector>
#include<string>
#include<random>
#include<algorithm>

#define DEFAULT_LENGTH 16

std::vector<char> generatePassword(int length);

int main(int argc, const char* argv[]) {
    std::vector<char> password;
    std::string input;
    int length;

    std::cout<<"Please enter the desired length of your password.\nKeep in mind, there is no max length,"
    "however very large passwords will take long to generate.\nEnter nothing for a default length of 16.\n";
    

    //accept input
    std::getline(std::cin, input);
    if(input.empty()) {
        //A default length is set in case the user inputs nothing.
        length = DEFAULT_LENGTH;
    }
    else {
        try {
            length = std::stoi(input);
        }
        catch(const std::exception& e) {
            std::cerr<<"Invalid input\n";
            return -1;
        }
    }
    password = generatePassword(length);

    std::cout<<"Your newly generated password: ";
    for(auto x : password) {
        std::cout<<x;
    }
    std::cout<<'\n';
    
    return 0;

}

//returns a vector of chars as the password
std::vector<char> generatePassword(int length) {
    std::vector<char> password;

    //Our PRNG engine. Grabs a number between 33 and 126 and then converts that number into a char for the vector.
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(33,126); // distribution in range [33, 126]

    for(int i = 0; i < length; i++) {
        password.push_back(dist6(rng));
    }

    //shuffle the vector for good measure
    auto shuffle = std::default_random_engine{};
    std::shuffle(std::begin(password), std::end(password), shuffle);

    return password;
}