//Implementation of FileWrapper
#include<iostream>
#include<fstream>
#include<cctype>
#include<cstdlib>
#include<sys/types.h>
#include<sys/stat.h>
#include<vector>
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
        std::cout<<line<<'\n';
    }
    file.close();
}

bool FileWrapper::searchFileFirst(std::string query) {
    //goes through each individual line in the file and searches for the query
    file.open(filename, FILE_READ);
    for(std::string line; std::getline(file, line);) {
        if(line.find(query) != std::string::npos) {
            std::cout<<"Pattern found in file\n";
            std::cout<<line;
            file.close();
            return true;
        }
    }
    std::cout<<"Pattern not found in file\n";
    file.close();
    return false;
}

//TO BE DONE
// bool FileWrapper::searchFileAll(std::string query) {
//     //our container with all the instances of the pattern
//     std::vector<std::string> patterns;


// }

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

//returns a size of -1 if an error was found
void FileWrapper::fileSize(int& bytes) {
    struct stat stbuf;
    if(stat(filename.c_str(), &stbuf) == -1) {
        std::cerr<<"fileSize: Cannot access "<<filename<<'\n';
        bytes = -1;
        return;
    }
    bytes = stbuf.st_size;

    return;
}

