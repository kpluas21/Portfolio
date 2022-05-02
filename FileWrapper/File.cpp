//Implementation of FileWrapper
#include<iostream>
#include<fstream>
#include<sstream>
#include<cctype>
#include<cstdlib>
#include"File.h"

FileWrapper::FileWrapper() {
    filename = "new_file.txt";

    //we open the file to make sure we dont accidentally overwrite it
    file.open(filename, FILE_READ);
    if(!file) {
        std::cerr<<"Error opening file\n";
        isOK = false;
    }
    file.close();

}

FileWrapper::FileWrapper(std::string filename) {
    this->filename = filename;
    
    //we open the file to make sure we dont accidentally overwrite it
    file.open(filename, FILE_READ);
    if(!file) {
        std::cerr<<"Error opening file\n";
        isOK = false;
    }
    file.close();

}


void FileWrapper::appendToFile(std::string text) {
    file.open(filename, FILE_WRITE | FILE_APPEND);
    file<<text;
    file.close();
}

void FileWrapper::printFile() {
    file.open(filename, FILE_READ);
    std::string line;
    while(std::getline(file, line)) {
        std::cout<<line;
    }
    file.close();
}

int FileWrapper::fileStats(int& chars, int& words, int& lines) {
    char cur = '\0';
    char last = '\0';
    chars = words = lines = 0;
    file.open(filename, FILE_READ);
    while(file.get(cur)) {
        if(cur == '\n' || (cur == '\f' && last == '\r')) {
            lines++;
        }
        else { 
            chars++;
        }
        if(!std::isalnum(cur) && std::isalnum(last)) { //this is the end of a word
            words++;
        }
        last = cur;
    }
    if(chars > 0) {
        if(std::isalnum(last)) { //counts for special case
            words;
        }
        lines++;
    }
    file.close();
    return words;
}

int FileWrapper::fileSize() {
    struct stat stbuf;
    if(stat(filename.c_str(), &stbuf) == -1) {
        std::cerr<<"fileSize: Cannot access "<<filename<<'\n';
        return -1;
    }
    return stbuf.st_size;
}

