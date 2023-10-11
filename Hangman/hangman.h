/**
 * @file hangman.h
 * @author Kevin Pluas
 * @brief Declarations for the functions used in hangman.cpp
 * @version 0.1
 * @date 2023-10-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef _HANGMAN_H
#define _HANGMAN_H

#include<vector>
#include<iostream>



/**
 * @brief Returns a random integer between 1 and 837 inclusive.
 * 
 * @return int 
 */
int random_i(void);

/**
 * @brief The main game loop. Repeats until the user quits.
 * 
 * @return int 
 */
int main_loop(void);

/**
 * @brief Compares the selected word with the guessed word. Returns a 0 which is a win condition. 1 otherwise.
 * 
 * @param word The word the user is trying to guess
 * @param word_blank The letters the user has guessed correctly so far
 * @return int 
 */
int check_win(std::string word, std::vector<char>& word_blank);


/**
 * @brief Grabs a word from the word list file. 
 * 
 * @return std::string The word to be guessed, or an empty string "" on error.
 */
std::string new_word(void);

/**
 * @brief Grabs a single char from the user through cin. 
 * 
 * @param guessed_char The vector of characters that the user has attempted to guess already to prevent duplicate guesses.
 * @return char 
 */
char get_char(std::vector<char>& guessed_char);

/**
 * @brief Draws the current hangman state
 * 
 * @param tries The number of incorrect guesses
 * @param hangman_g A string vector containing our graphics
 * @param word_blank The current state of our word guess
 * @param guessed_chars The letters the user has used already
 */
void draw(int& tries, std::vector<std::string>& hangman_g, std::vector<char>& word_blank, std::vector<char>& guessed_chars);

#endif //_HANGMAN_H