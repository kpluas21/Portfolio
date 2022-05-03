#ifndef FILE_H
#define FILE_H

//A wrapper for C++'s fstream class
//This is meant to hopefully help streamline C++ file I/O. 
//This class uses a single fstream object for a file. Each time a certain function gets called, the file open with a specifc mode depending on the function. 
//Therefore there is no need to keep track of the current read/write mode of a file. The class handles that for you.
/*-------------------------------------------------------------------------------------------------------------------
IMPORTANT NOTES
    Make sure to create a backup of whatever file you plan on manipulating with this class.
    The onus is on the user to create this backup. The class will not do it automatically. 
    I've included a function that will do just that but a simple copy/paste will also suffice :)

    Check the status of the isOK variable after the creation of every object. 
*/

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
    
    //returns the file size in bytes. Returns a value of -1 if an error was found.
    void fileSize(int& bytes);

    //searches the file for a given string. If found, returns true and displays the line containing the first instance
    bool searchFileFirst(std::string query);

    //WIP
    //same as searchFileFirst, however it outputs every line containing the pattern
    // bool searchFileAll(std::string query);

    //creates a backup of the current file with a '.bak' extension
    void createBackup();

    //a state check to make sure the object was constructed okay. It should be checked after construction.
    bool isOK = true;
    
    //check if a file already exists with a given filename
    bool fileExists(const std::string& name);
private:
    //this will handle both input and output
    std::fstream file;

    //used for backup and copying functions. Helps with readability.
    std::fstream src;
    std::fstream dest;

    //name of both the file and backup file.
    std::string filename;
    std::string backupFilename;

};

#endif //FILE_H