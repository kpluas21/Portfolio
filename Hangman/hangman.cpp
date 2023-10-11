/**
 * @file hangman.cpp
 * @author Kevin Pluas
 * @brief main driver code for hangman
 * @version 0.1
 * @date 2023-10-10
 *
 * @copyright Copyright (c) 2023
 *
 */
/*As of right now this program works decently. It will grab a random word and create an old fashioned game of hangman around that word.
So far some possible improvements include the addition of guessing the entire word ala Wheel of Fortune. Also I dont feel super great about clearing the entire terminal screen but I dont
have any suitable replacements outside of a full GUI library which I didn't want to use for something this small.

Just make sure that the word_list file is in the same directory as the executable and it should work without a hitch.*/

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>
#include <algorithm>
#include <ctype.h>

#include "hgraphics.h"
#include "hangman.h"

static flags = 0; //

// calls and controls the main game loop
int main(void)
{

    // keeps the user playing the game unless a nonzero value is received, ending the game and thus the program
    // every time main loop starts over a brand new game starts
    while (main_loop() == 0)
        ;

    return 0;
}

// has all the main game stuff.
// each loop will create all of the objects needed to play a full game of hangman
int main_loop(void)
{
    std::string word = new_word();
    if (word.length() == 0)
    {
        return 1;
    }

    int tries = 0; // the number of times a player has failed at guessing a character. End the game when it reaches 7.
    char guess;    // self explanatory

    std::vector<char> guessed_char; // this vector holds each of the unique letters guessed during the game
    std::vector<char> word_blank;   // create a container to hold the word blanks AKA the word as it currently stands

    for (auto x : word)
        word_blank.push_back('_');

    do // ACTUAL main loop
    {
        draw(tries, hangman_g, word_blank, guessed_char); // draw the main screen

        // DEBUG: SHOWS BACKGROUND VARIABLES
        std::cout << word << '\n';
        std::cout << tries << '\n';
        std::cout << word_blank.size() << '\n';

        // ACCEPT INPUT
        guess = get_char(guessed_char); // grab a single character/letter as input.

        if (word.find(guess) != std::string::npos) // if the guess is in word...
        {
            for (int i = 0; i < word.length(); i++) // loop through the word
            {
                if (guess == word[i]) // if guess and letter in word match then....
                {
                    word_blank[i] = guess; // replace the blank with the guess using the index
                }
            }
        }
        else
            tries++; // letter wasnt found in the word, increase tries and update hangman

        guessed_char.push_back(guess); // put the guess, whether correct or otherwise, in the list of tried letters. Prevent the player from using them again

        std::string word_blank_asString(word_blank.begin(), word_blank.end());

        draw(tries, hangman_g, word_blank, guessed_char);

        if (tries == 6) // if player loses
        {
            std::cout << "YOU LOSE!\n";
            std::cout << "The word was: " << word << "...\n";
            break; // break out of the loop to allow a new game
        }

        else if (word == word_blank_asString) // if the word is correct
        {

            std::cout << "YOU WIN!\n";
            std::cout << "The word was: " << word << "!\n";
            break; // break out of the loop to allow a new game
        }

    } while (true); // repeat indefinitely until either of the two previous checks returns true

    std::cout << "Play again? (Y/N): ";
    char c;

    std::cin >> c;

    if (c == 'y' || c == 'Y')
    {
        // prevents an extra prompt from appearing on repeat games
        std::cin.ignore();

        // return 0 and start a new game
        return 0;
    }

    // end the game and the program
    return 1;
}

// pulls and returns a random word from the file to use for the game
std::string new_word(void)
{
    // create and open the file object
    std::ifstream file;
    file.open("word_list");

    // check to see if file exists or has been moved elsewhere. Ends program if problem is found
    if (!file)
    {
        std::cerr << "Error: File invalid or does not exist\nHas it been moved? Ending program\n";
        return "";
    }

    std::string word;

    for (int i = 0, x = random_i(); i < x; i++) // we need to loop through the file to get the word we want and assign it to var word.
        std::getline(file, word, '\n');

    // file clean up
    file.close();

    return word;
}

// generate a random number for the file index
int random_i(void)
{
    std::random_device dev; // i still dont know how this PRNG bullshit works....
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 837);

    return dist6(rng);
}

// accepts a single char as input, rejects inputs bigger than a single character or characters already guessed.
char get_char(std::vector<char> &guessed_char)
{
    std::string input; // i use a string to allow the use of getline , this will help ensure only a single character is grabbed

    do
    {
        std::cout << "Enter a letter: ";
        std::getline(std::cin, input);

        // repeat if not an input of 1 character or the input is found in the guess characters vector meaning a duplicate  guess OR its not a letter
    } while (input.length() != 1 || (std::find(guessed_char.begin(), guessed_char.end(), input[0]) != guessed_char.end()) || (!isalpha(input[0])));

    return input[0]; // ensures a return of a single char.
}

// This function will grab the respective arguments and display them to the user.
// use a reference to avoid making another copy.
void draw(int &tries, std::vector<std::string> &hangman_g, std::vector<char> &word_blank, std::vector<char> &guessed_chars)
{
    // clear the screen to give the illusion of updating graphics(?)
    system("clear");

    // show current hangman
    std::cout << hangman_g[tries];
    std::cout << '\n';

    // show current word blanks
    for (auto x : word_blank)
        std::cout << x << " ";

    std::cout << '\n';

    // show the letters that have been already used, correct or otherwise
    for (auto x : guessed_chars)
        std::cout << x << " ";

    std::cout << '\n';

    return; // probably unneccesary but good for readability
}
