#include <bits/stdc++.h>
using namespace std;
string encrypt(string s, int l)
{
    int len = sqrt(l - 1) + 1;
    vector<string> matrix(len, string(len, '*'));
    int idx = 0;
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            matrix[i][j] = s[idx++];
        }
    }
    string ret = "";
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            ret += matrix[j][i];
        }
    }
    return ret;
}
string decrypt(string s, int l)
{
    return encrypt(s, l).substr(0, l);
}
int main()
{
    string s;
    cout << "Enter a string: ";
    cin >> s;
    int l = s.length();
    string encrypted = encrypt(s, l);
    cout << "The encrypted string is: " << encrypted << endl;
    string decrypted = decrypt(encrypted, l);
    cout << "After decryption: " << decrypted << endl;
}