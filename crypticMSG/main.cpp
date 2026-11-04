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
#include <array>
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


void keyGen(){
    crypto_box_keypair(publicKey.data(), PrivateKey.data());
    ofstream publicfKey("public.fkey", ios::binary);
    publicfKey.write(reinterpret_cast<const char*>(publicKey.data()), publicKey.size());
    publicfKey.close();
    cout<<"Public key generated!\n";
    
    ofstream PrivatefKey("private.fkey", ios::binary);
    PrivatefKey.write(reinterpret_cast<const char*>(PrivateKey.data()), PrivateKey.size());
    PrivatefKey.close();
    cout<<"Private key generated!\n";
}

void keyLoad(){
    ifstream publicfKey("public.fkey", ios::binary);
    if(!publicfKey.is_open()){
        cout<<"Failed to load public key from file"<<endl;
        keyGen();
        return;
    }
    publicfKey.read(reinterpret_cast<char*>(publicKey.data()), publicKey.size());
    publicfKey.close();
    
    
    ifstream privatefKey("private.fkey", ios::binary);
    if(!privatefKey.is_open()){
        cout<<"Failed to private load key from file"<<endl;
        keyGen();
        return;
    }
    privatefKey.read(reinterpret_cast<char*>(PrivateKey.data()), PrivateKey.size());
    
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
