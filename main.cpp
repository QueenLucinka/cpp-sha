#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct Data{
    string input;
    string randomNumber;
    string concatInputRandom;
    string hashedData;

    // Function to generate random number
    string generateRandomNumber(){
        int n = 10;
        string randomStr;
        for(int i = 0; i < n; i++) {
            char random_char = '0' + rand() % 10;
            randomStr.push_back(random_char);
        }
        return randomStr;
    }

    // User input function
    void userInput(){
        cout << "Input: ";
        cin >> input;
    }

    // Concatenate input and random number
    void concatenateInputRandom(){
        userInput();
        randomNumber = generateRandomNumber();
        concatInputRandom = input + randomNumber;
        cout << "Concatenated string: " << concatInputRandom << endl;
    }

    // SHA256 hashing function
    void hashSHA256(const string& input, string& hashed){
        SHA256_CTX ctx;
        SHA256_Init(&ctx);
        SHA256_Update(&ctx, input.c_str(), input.length());

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_Final(hash, &ctx);

        stringstream ss;
        for(int i = 0; i < SHA256_DIGEST_LENGTH; ++i){
            ss << hex << setw(2) << setfill('0') << static_cast<int>(hash[i]);
        }

        hashed = ss.str();
    }

    // Hash concatInputRandom
    void hashConcatInputRandom(){
        hashSHA256(concatInputRandom, hashedData);
        cout << "Hashed data: " << hashedData << endl;
    }
};

int main(){
    const int ARRAY_SIZE = 25;
    Data data;
    string hashedArray[ARRAY_SIZE];

    for(int i = 0; i < ARRAY_SIZE; ++i){
        data.concatenateInputRandom(); // Concatenate input and random number
        data.hashConcatInputRandom(); // Hash concatenated data
        hashedArray[i] = data.hashedData; // Store hashed string in the array
    }

    // Print the hashed strings stored in the array
    cout << "Hashed strings stored in the array:" << endl;
    for(int i = 0; i < ARRAY_SIZE; ++i){
        cout << hashedArray[i] << endl;
    }

    return 0;
}

