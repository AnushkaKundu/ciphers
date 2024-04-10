#include <bits/stdc++.h>
using namespace std;

map<char, pair<int, int>> keyVal;
vector<string> matrix(5, string(5, '*'));
char findChar(char i)
{
    if (i == 'j')
        return 'i';
    return i;
}
void generateKeyMatrix(string key)
{
    map<char, bool> used;
    string filler = "";
    for (auto ele : key)
    {
        if (used[findChar(ele)] == 0)
        {
            used[findChar(ele)] = 1;
            filler += findChar(ele);
        }
    }
    for (char i = 'a'; i <= 'z'; i++)
    {
        if (i == 'j')
            continue;
        if (used[i] == 0)
        {
            filler += i;
        }
    }
    int k = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            matrix[i][j] = filler[k];
            keyVal[findChar(filler[k])] = {i, j};
            k++;
            // cout << matrix[i][j] << " ";
        }
        // cout << endl;
    }
}
void printKeyMatrix(string key)
{
    generateKeyMatrix(key);
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
vector<string> findDigrams(string s)
{
    string digram = "";
    bool isSingle = 0;
    vector<string> digrams;
    for (int i = 0; i < s.length(); i++)
    {
        char ele = s[i];
        if (!isSingle)
        {
            digram += ele;
            isSingle = 1;
        }
        else
        {
            if (ele == digram[0])
            {
                digram += 'z';
                i--;
            }
            else
            {
                digram += ele;
            }
            digrams.push_back(digram);
            digram = "";
            isSingle = 0;
        }
    }
    if (isSingle)
    {
        if (digram[0] == 'z')
            digram += 'x';
        else
            digram += 'z';
        digrams.push_back(digram);
    }
    return digrams;
}
void printDiagrams(string plainText)
{
    vector<string> digrams = findDigrams(plainText);
    for (auto ele : digrams)
        cout << ele << " ";
    cout << endl;
}
string findEncryptDigram(vector<string> matrix, string s, map<char, pair<int, int>> &keyVal)
{
    pair<int, int> c1, c2;
    c1 = keyVal[s[0]];
    c2 = keyVal[s[1]];
    string ret(2, '*');
    if (c1.first == c2.first)
    {
        ret[0] = matrix[c1.first][(c1.second + 1) % 5];
        ret[1] = matrix[c2.first][(c2.second + 1) % 5];
    }
    else if (c1.second == c2.second)
    {
        ret[0] = matrix[(c1.first + 1) % 5][c1.second];
        ret[1] = matrix[(c2.first + 1) % 5][c2.second];
    }
    else
    {
        ret[0] = matrix[c1.first][c2.second];
        ret[1] = matrix[c2.first][c1.second];
    }
    return ret;
}
string encrypt(string plainText)
{
    vector<string> digrams = findDigrams(plainText);
    string op = "";
    for (auto ele : digrams)
        op += findEncryptDigram(matrix, ele, keyVal);
    return op;
}
string findDecryptDigram(vector<string> matrix, string s, map<char, pair<int, int>> &keyVal)
{
    pair<int, int> c1, c2;
    c1 = keyVal[s[0]];
    c2 = keyVal[s[1]];
    string ret(2, '*');
    if (c1.first == c2.first)
    {
        ret[0] = matrix[c1.first][(c1.second + 4) % 5];
        ret[1] = matrix[c2.first][(c2.second + 4) % 5];
    }
    else if (c1.second == c2.second)
    {
        ret[0] = matrix[(c1.first + 4) % 5][c1.second];
        ret[1] = matrix[(c2.first + 4) % 5][c2.second];
    }
    else
    {
        ret[0] = matrix[c1.first][c2.second];
        ret[1] = matrix[c2.first][c1.second];
    }
    return ret;
}
string decrypt(string encryptedText)
{
    vector<string> digrams = findDigrams(encryptedText);
    // for (auto ele : digrams)
    //     cout << ele << " ";
    // cout << endl;
    string op = "";
    for (auto ele : digrams)
    {
        string part = findDecryptDigram(matrix, ele, keyVal);
        op += part;
        // cout << part << " ";
    }
    // cout << endl;
    return op;
}
int main()
{
    string key, plaintext;
    cout << "Enter the key: ";
    cin >> key;
    cout << "The key matrix is: " << endl;
    printKeyMatrix(key);
    cout << "Enter the plaintext: ";
    cin >> plaintext;
    cout << "The digrams of the plaintext are: ";
    printDiagrams(plaintext);
    string encrypted = encrypt(plaintext);
    cout << "The encrypted string is: " << encrypted << endl;
    string decrypted = decrypt(encrypted);
    cout << "The decrypted string is: " << decrypted << endl;
    return 0;
}