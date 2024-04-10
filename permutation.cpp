#include <bits/stdc++.h>
using namespace std;
vector<int> factorial(int n)
{
    vector<int> fact(n + 1, 1);
    for (int i = 2; i <= n; i++)
        fact[i] = i * fact[i - 1];
    return fact;
}
string permute(string s, int n, int key)
{
    vector<int> fact = factorial(n);
    vector<int> permutation(n, -1);
    for (int i = n; i > 0; i--)
    {
        int t = key / fact[i - 1];
        key %= fact[i - 1];
        for (int j = 0; j < n; j++)
        {
            if (permutation[j] != -1)
                continue;
            if (t == 0)
            {
                permutation[j] = n - i;
                break;
            }
            t--;
        }
    }
    string res(n, '*');
    for (int i = 0; i < n; i++)
    {
        res[permutation[i]] = s[i];
    }
    return res;
}
string encrypt(string s, int blockSize, int key)
{
    string op = "";
    int l = s.length();
    int app = (blockSize - (l % blockSize)) % blockSize;
    string t(app, '*');
    s += t;
    int blocks = s.length() / blockSize;
    for (int i = 0; i < blocks; i++)
    {
        op += permute(s.substr(i * blockSize, blockSize), blockSize, key);
    }
    return op;
}
string backPermute(string s, int n, int key)
{
    vector<int> fact = factorial(n);
    vector<int> permutation(n, -1);
    for (int i = n; i > 0; i--)
    {
        int t = key / fact[i - 1];
        key %= fact[i - 1];
        for (int j = 0; j < n; j++)
        {
            if (permutation[j] != -1)
                continue;
            if (t == 0)
            {
                permutation[j] = n - i;
                break;
            }
            t--;
        }
    }
    string res(n, '*');
    for (int i = 0; i < n; i++)
    {
        res[i] = s[permutation[i]];
    }
    return res;
}
string decrypt(string s, int blockSize, int key)
{
    string op = "";
    int blocks = s.length() / blockSize;
    for (int i = 0; i < blocks; i++)
    {
        op += backPermute(s.substr(i * blockSize, blockSize), blockSize, key);
    }
    return op;
}
int main()
{
    string s;
    cout << "Enter a string: ";
    cin >> s;
    int blockSize = 10;
    int key = 1;
    int fact = (factorial(blockSize))[blockSize] - 1;
    cout << "Enter a key from 0 to " << fact << ": ";
    cin >> key;
    if (key > fact)
        cout << "Key should be smaller than " << fact << endl;
    string encrypted = encrypt(s, blockSize, key);
    cout << "The encrypted string is: " << encrypted << endl;
    string decrypted = decrypt(encrypted, blockSize, key);
    cout << "After decryption: " << decrypted << endl;
    return 0;
}