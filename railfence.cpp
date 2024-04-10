#include <bits/stdc++.h>
using namespace std;
vector<int> fX(int len, int depth)
{
    int m = len + 2 * depth - 3;
    int n = 2 * (depth - 1);
    int x = (m + n - 1) / n;
    int expectedLen = x * (2 * depth - 2) - 2 * depth + 3;
    vector<int> lengths(depth, (x - 1) * 2);
    lengths[0] = x;
    lengths[depth - 1] = x - 1;
    bool direction = 0;
    int rail = 0;
    while (expectedLen != len)
    {
        lengths[rail]--;
        if (direction == 0)
            rail++;
        else if (direction == 1)
            rail--;
        if (rail == depth)
        {
            rail -= 2;
            direction = 1;
        }
        else if (rail == -1)
        {
            rail = 1;
            direction = 0;
        }
        expectedLen--;
    }

    return lengths;
}
string railfence(string s, int depth)
{
    int len = s.length();
    bool direction = 0; // 0 = down, 1 = up
    vector<string> rf(depth, "");
    int rail = 0;
    for (int i = 0; i < s.length(); i++)
    {
        rf[rail] += s[i];
        // cout << rail << endl;
        if (direction == 0)
            rail++;
        else if (direction == 1)
            rail--;
        if (rail == depth)
        {
            rail -= 2;
            direction = 1;
        }
        else if (rail == -1)
        {
            rail = 1;
            direction = 0;
        }
    }
    // return s;
    string t = "";
    for (auto ele : rf)
        t += ele;
    return t;
    // return t.substr(0, len);
}
string decrypt(string s, int depth)
{
    vector<int> lengths = fX(s.length(), depth);
    // for (auto ele : lengths)
    //     cout << ele << " ";
    vector<string> rails(depth);
    int run = 0;
    for (int i = 0; i < depth; i++)
    {
        int ele = lengths[i];
        rails[i] = s.substr(run, ele);
        run += ele;
    }
    // for (auto ele : rails)
    //     cout << ele << endl;
    vector<int> curidx(depth, 0);
    int rail = 0;
    int direction = 0;
    string regen = "";
    for (int i = 0; i < s.length(); i++)
    {
        regen += rails[rail][curidx[rail]];
        curidx[rail]++;
        if (direction == 0)
            rail++;
        else if (direction == 1)
            rail--;
        if (rail == depth)
        {
            rail -= 2;
            direction = 1;
        }
        else if (rail == -1)
        {
            rail = 1;
            direction = 0;
        }
    }
    return regen;
}
int main()
{
    string s;
    cout << "Enter a string: ";
    cin >> s;

    // length 2
    string railFence2 = railfence(s, 2);
    string decryptedRF2 = decrypt(railFence2, 2);
    cout << "After applying railfence with depth = 2: " << railFence2 << endl;
    cout << "After decrypting: " << decryptedRF2 << endl;

    string railFence3 = railfence(s, 3);
    string decryptedRF3 = decrypt(railFence3, 3);
    cout << "After applying railfence with depth = 3: " << railFence3 << endl;
    cout << "After decrypting: " << decryptedRF3 << endl;

    string railFence4 = railfence(s, 4);
    string decryptedRF4 = decrypt(railFence4, 4);
    cout << "After applying railfence with depth = 4: " << railFence4 << endl;
    cout << "After decrypting: " << decryptedRF4 << endl;
    return 0;
}