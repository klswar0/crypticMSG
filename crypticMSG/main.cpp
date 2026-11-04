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


void FileCreate(string text){
    ofstream file("message.txt");
    if(!file.is_open()){
        cerr<<"Failed to create file"<<endl;
        return;
    }
    file<<text;
    
}

void decrypt(string text) {
    // conversion from hex needed DONE
    
    vector<unsigned char> converted(text.size()/2);
    
    sodium_hex2bin(converted.data(), converted.size(), text.data(), text.size(), NULL, NULL, NULL);
    
    vector<unsigned char> decryptedM(converted.size());
    if(crypto_box_seal_open(decryptedM.data(),
                            converted.data(),
                            converted.size(),
                            publicKey.data(),
                            PrivateKey.data()
                            ) !=0)
    {
        cerr<<"Decryption failed"<<endl;
    
    }
    string fullyDecrypted(decryptedM.begin(), decryptedM.end());
    cout<<"Decrypted message: "<<fullyDecrypted<<endl;
    FileCreate(fullyDecrypted);
}

void encrypt(string text) {
    
    vector<unsigned char> encprytedM(text.size()+crypto_box_SEALBYTES);
    if (crypto_box_seal(
                        encprytedM.data(),
                        reinterpret_cast<const unsigned char*>(text.data()),
                        text.size(),
                        publicKey.data()
                        )!=0)
    {
        cerr<<"Encryption failed"<<endl;
        
    }
    // needs conversion to print DONE
    vector<char> hexString(encprytedM.size() * 2 + 1);
    sodium_bin2hex(hexString.data(), hexString.size(), encprytedM.data(), encprytedM.size());
    cout<<"Encrypted message: "<<hexString.data()<<endl;
    FileCreate(hexString.data());
}

void inputManager(string type,string text) {
    string input;
    cout<<text<<endl<<"enter the text:";
    cin>>input;
    if (type =="Encrypt"){
        encrypt(input);
    }
    else if (type =="Decrypt"){
        decrypt(input);
    }
}


int main(int argc, const char * argv[]) {
    if (sodium_init() < 0) {
        cerr << "Failed to initialize libsodium" << endl;
    }

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
            inputManager("Encrypt","Encrypting");
        }
        else if (choice == 2){
            inputManager("Decrypt","Decrypting");
        }
        
    }

            
    
    
    return EXIT_SUCCESS;
}
