#include<iostream>
#include"File.h"

int main(void) {
    FileWrapper fw("romeoAndJuliet");
    if(fw.isOK == false) {
        return -1;
    }
    fw.createBackup();
    return 0;
}