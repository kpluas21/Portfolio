#ifndef FILE_H
#define FILE_H

//A wrapper for C++'s fstream class
//This will help streamline file i/o and can also handle multiple files (to be implemented)
#include<iostream>
#include<fstream>

//some macros to help with readability
#define FILE_READ std::ios::in
#define FILE_WRITE std::ios::out
#define FILE_APPEND std::ios::app

class FileWrapper{
public:
    //the ctor will accept no arguments by default, simply creating a new file
    //otherwise, open an existing file for reading/writing
    //isOK should be checked after creating the object.
    FileWrapper();
    FileWrapper(std::string filename);

    //appends the given string argument to the end of the file
    void appendToFile(std::string text);

    //prints the entire contents of the file to std::cout
    void printFile();

    //Counts the numbers of chars, words and lines in the current file.
    //Returns ints.
    int fileStats(int& chars, int& words, int& lines);
    
    //returns the file size in bytes
    int fileSize();

    //a state check to make sure the object was constructed okay. It should be checked after construction.
    bool isOK = true;
private:
    //this will handle both input and output
    std::fstream file;
    //name of the file
    std::string filename;
};

#endif //FILE_H