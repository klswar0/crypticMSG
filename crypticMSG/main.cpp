//
//  main.cpp
//  crypticMSG
//
//  Created by Ksawery Lewandowski on 21/10/2026.
//

#include <iostream>
#include <fstream>
#include <sodium.h>
#include <fstream>
using namespace std;

string key="";

//void keySel() {
//    
//}
//
//void keyFind(string ID){
//
//    
//}
//
//void keyAdd(string ID,string key,string name) {
//ofstream keyFile("contacts.txt");
//    keyFile<<"--KEY INFO--\n"
//    <<"Key ID: "<<ID<<endl
//    <<"Name: "<<name<<endl
//    <<"Key: "<<key<<endl
//    <<"----------------\n";
//    
//}
//
array<unsigned char, crypto_box_PUBLICKEYBYTES> publicKey;
array<unsigned char, crypto_box_SECRETKEYBYTES> PrivateKey;

void keyLoad(){
    ifstream publicfKey("public.fkey");
    if(!getline(publicfKey, key)){
        cout<<"Failed to load key from file"<<endl;
    }
    publicfKey.close();
    ifstream privatefKey("private.fkey");
    if(!getline(privatefKey, key)){
        cout<<"Failed to load key from file"<<endl;
    }
    
    privatefKey.close();
    
}



void decrypt() {}

void encrypt() {}



int main(int argc, const char * argv[]) {
    if (sodium_init() < 0) {
        cerr << "Failed to initialize libsodium" << endl;
    }
//    bool encrypt = true;
//    string message = "";
//    if(encrypt) {
//        ifstream inputFile("input.txt");
//        string line;
//        while(getline(inputFile, line)) {
//            message += line + "\n";
//        }
//    }
    keyLoad();
    while(true){
        cout<<"Action:\n"
        <<"1. Encrypt\n"
        <<"2. Decrypt\n"
        <<"3. Exit\n";
        int choice;
        cin>>choice;
        if(choice == 3){
            break;
        }
        if(choice == 1){
            encrypt();
        }
        else if (choice == 2){
            decrypt();
        }
        
    }

            
    
    
    return EXIT_SUCCESS;
}
