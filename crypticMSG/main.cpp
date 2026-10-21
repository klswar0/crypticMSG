//
//  main.cpp
//  crypticMSG
//
//  Created by Ksawery Lewandowski on 21/10/2026.
//

#include <iostream>
#include <fstream>
#include <sodium.h>
using namespace std;
int main(int argc, const char * argv[]) {
    bool encrypt = true;
    string message = "";
    if(encrypt) {
        ifstream inputFile("input.txt");
        string line;
        while(getline(inputFile, line)) {
            message += line + "\n";
        }
    }
            
    
    
    return EXIT_SUCCESS;
}
