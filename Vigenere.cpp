const char *question = R""""(
Design and implement a program to perform encryption and decryption
using the Vigenère Cipher with repeating keywords. Consider the following
inputs for the program.
For Encryption:
a) Input1 – Plaintext and Key
b) Output1 – Ciphertext
For Decryption
Input2- Ciphertext
Output2- Plaintext
)"""";

#include <bits/stdc++.h>
using namespace std;

string encrypt(string plaintext, string key)
{
    int plen = plaintext.length();
    int klen = key.length();
    int times = 1 + (plen - 1) / klen;
    string KEY = "";
    for (int i = 0; i < times; i++)
        KEY += key;
    KEY = KEY.substr(0, plen);
    string output(plen, '.');
    for (int i = 0; i < plen; i++)
    {
        char c1 = plaintext[i];
        char c2 = KEY[i];
        int i1 = c1 - 'A';
        int i2 = c2 - 'A';
        int ii = i1 + i2;
        ii %= 26;
        char c = ii + 'A';
        output[i] = c;
    }
    return output;
}
string decrypt(string ciphertext, string key)
{
    int klen = key.length();
    string decryptKEY(klen, '.');
    for (int i = 0; i < klen; i++)
    {
        int k = key[i] - 'A';
        k = 26 - k;
        k %= 26;
        char c = k + 'A';
        decryptKEY[i] = c;
    }
    return encrypt(ciphertext, decryptKEY);
}
void getInputs(string &plaintext, string &key)
{
    ifstream inputFile("Vigenere.txt");

    if (inputFile.is_open())
    {
        getline(inputFile, plaintext);
        getline(inputFile, key);
        inputFile.close();
    }
    else
    {
        cerr << "Unable to open file input.txt." << endl;
        exit(0);
    }
}
int main()
{
    string plaintext, key, ciphertext, decryptedtext;
    getInputs(plaintext, key);
    cout << "Plaintext: " << plaintext << endl;
    cout << "Key: " << key << endl;
    ciphertext = encrypt(plaintext, key);
    cout << "The cipher text: " << ciphertext << endl;
    decryptedtext = decrypt(ciphertext, key);
    cout << "The decrypted text: " << decryptedtext << endl;
}