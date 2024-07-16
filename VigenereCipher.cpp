// VigenereCipher.cpp
// This is a program that lets the user employ a Vigenere Cipher on a message and key of their choice
// The key is then iterated through for each character in the word and the alphabet is shifted a certain amount based on the character in the key
//
// Potential Next Steps:
//  - Adding a decrypter
//  - Exception Handling for direction characters and shift values
//  - Add Unit Tests
//  - Add Frequency Analysis for unknown keys
#include <iostream>
#include <string>
#include <limits>

using namespace std;

int char2num(char C) {
    // Inputs:
    //
    // char C: Takes in a character value
    //
    // Output:
    //
    // Maps a value from 0 to 51 and will give the character the proper index of the alphabet string to be traversed  
    //
    if (C >= 'a' && C <= 'z') {
        return C - 'a'; //Maps a -> 0, b -> 1, ..., z -> 25
    }
    else if (C >= 'A' && C <= 'Z') {
        return C - 'A' + 26; //Maps A -> 26, B -> 27, ..., Z -> 51
    }
    else {
        return static_cast<int>(C) + 60; //If this else block is reached, then its outside of the range of the alphabet and thus will not be affected by the cipher.
        //Returns a value outside of the range of 0 to 51 in order to prevent certain ascii values being used for spaces and other characters in the key
    }
}

string alphaShift(string alpha, int shift) {
    // Inputs:
    //
    // string alpha: A string containing the alphabet in order
    // int shift: An integer determining how far the alphabet will be shifted
    //
    // Output:
    //
    // newAlpha: Returns the new left-shifted alphabet that will be used to encode our message,
    
    if (shift == 0) {
        return alpha;        
    }
    
    string firstPiece;
    string lastPiece;
    string newAlpha;

    firstPiece = alpha.substr(0, shift);
    lastPiece = alpha.substr(shift);
    newAlpha = lastPiece + firstPiece;
    return newAlpha;
    
}

string vigenereEncrypt(string alpha, string alphaCap, string message, string key) {
    // Input:
    //
    // string shiftedAlpha: Our shifted lowercase alphabet
    //
    // string shiftedAlphaCap: Our shifted uppercase alphabet
    //
    // string message: Our message to be encrypted
    // 
    // string key: key that will determine how the scheme encrypts the message
    //
    //
    // Output:
    //
    // Returns a copy of our encrypted message using the vigenere shifting scheme
    int length = message.length();
    int keylength = key.length();
    int j = 0; //used to index through the key
    string strCopy = message;
    string shiftedAlpha;
    string shiftedAlphaCap;
    for (int i = 0; i < length; i++) {
        if(char2num(strCopy[i]) >= 0 && char2num(strCopy[i]) <= 25) {
            shiftedAlpha = alphaShift(alpha, char2num(key[j % keylength]) % 26);
            strCopy[i] = shiftedAlpha[char2num(strCopy[i])];
            j++;
        }
        else if(char2num(strCopy[i]) >= 26 && char2num(strCopy[i]) <= 51) {
            shiftedAlphaCap = alphaShift(alphaCap, char2num(key[j % keylength]) % 26);
            strCopy[i] = shiftedAlphaCap[char2num(strCopy[i]) - 26];
            j++;
        }
        else {
            strCopy[i] = strCopy[i];
        }
    }
    return strCopy;
}

int main() {

    //Start out by initializing our necessary variables

    string alphabet = "abcdefghijklmnopqrstuvwxyz"; // Lowercase alphabet to be shifted
    string alphabetCap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // Uppercase alphabet to be shifted
    bool flag = true; // Flag initialized to do repeated encryption
    int shiftVal; // Initializes our shift variable
    char cont; // Initializes our loop repetition variable
    string message; // Initializes our message variable
    string key; //intializes our key variable
    string encryptedMessage; // Initializes our encrpyted message variable
    string newAlpha; // Initializes our variable for our shifted lowercase alphabet
    string newAlphaCap; // Initializes our variable for our shifted uppercase alphabet

    cout << "Welcome to the Vigenere Cipher! Would you like to encrypt a message? (y or n)" << endl; 

    cin >> cont;

    if(cont == 'n') {
        flag = false;
    }

    while (flag) {

        cout << "What message would you like to encrypt?" << endl; 

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Clears our input buffer to be reused

        getline(cin, message); // Polls user for message input

        cout << "What will your key be?" << endl;

        //cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clears our input buffer to be reused

        getline(cin, key); // Polls user for key input

        //cout << "right before encrypt" << endl;

        encryptedMessage = vigenereEncrypt(alphabet, alphabetCap, message, key); // Encrypts the message

        cout << "Your Message is: " << message << endl;

        cout << "Your encrypted message is " << encryptedMessage << endl;

        cout << "Would you like to encrypt another message? (y or n)" << endl;

        cin >> cont; // Polls if user would like to continue

        if(cont == 'n') {
            flag = false; // This flag will escape the loops and end the program
        }

    }

    cout << "Thank you for encrypting!" << endl;

    return 0;
}