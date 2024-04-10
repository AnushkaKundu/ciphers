#include <bits/stdc++.h>
using namespace std;
int n = 0;
// int D(std::vector<std::vector<int>> &matrix, int size)
// {
//     int det = 0;
//     int sign = 1;
//     if (size == 1)
//     {
//         det = matrix[0][0];
//     }
//     else if (size == 2)
//     {
//         det = (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
//     }
//     else
//     {
//         for (int i = 0; i < size; i++)
//         {
//             std::vector<std::vector<int>> cofactor(size - 1, std::vector<int>(size - 1));
//             int sub_i = 0, sub_j = 0;
//             for (int j = 1; j < size; j++)
//             {
//                 for (int k = 0; k < size; k++)
//                 {
//                     if (k == i)
//                     {
//                         continue;
//                     }
//                     cofactor[sub_i][sub_j] = matrix[j][k];
//                     sub_j++;
//                 }
//                 sub_i++;
//                 sub_j = 0;
//             }
//             det += sign * matrix[0][i] * D(cofactor, size - 1);
//             sign = -sign;
//         }
//     }
//     return det;
// }

void getCofactor(const vector<vector<int>> &mat, vector<vector<int>> &temp, int p, int q, int n)
{
    int i = 0, j = 0;

    for (int row = 0; row < n; row++)
    {
        for (int col = 0; col < n; col++)
        {
            if (row != p && col != q)
            {
                temp[i][j++] = mat[row][col];

                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

int determinant(const vector<vector<int>> &mat, int n)
{
    int D = 0;

    if (n == 1)
        return mat[0][0];

    vector<vector<int>> temp(n, vector<int>(n));

    int sign = 1;

    for (int f = 0; f < n; f++)
    {
        getCofactor(mat, temp, 0, f, n);
        D += sign * mat[0][f] * determinant(temp, n - 1);

        sign = -sign;
    }

    return D;
}

void adjoint(const vector<vector<int>> &A, vector<vector<int>> &adj, int N)
{
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }

    int sign = 1;
    vector<vector<int>> temp(N, vector<int>(N));

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            getCofactor(A, temp, i, j, N);

            sign = ((i + j) % 2 == 0) ? 1 : -1;

            adj[j][i] = (sign) * (determinant(temp, N - 1) % 26);
            adj[j][i] = (adj[j][i] + 26) % 26;
        }
    }
}
int modInv(int A, int M)
{
    if (__gcd(A, M) != 1)
        return -1;
    A %= M;
    int m0 = M;
    int y = 0, x = 1;

    if (M == 1)
        return 0;

    while (A > 1)
    {
        // q is quotient
        int q = A / M;
        int t = M;

        // m is remainder now, process same as
        // Euclid's algo
        M = A % M, A = t;
        t = y;

        // Update y and x
        y = x - q * y;
        x = t;
    }

    // Make x positive
    if (x < 0)
        x += m0;

    return x;
}
void invert(const vector<vector<int>> &A, vector<vector<int>> &inverse, int N, bool &found)
{
    int det = determinant(A, N) % 26;
    if (det == 0)
    {
        cout << "Singular matrix, can't find its inverse";
        found = 0;
        // exit(0);
        return;
    }
    int inv = modInv(det + 26, 26);
    if (inv == -1)
    {
        cout << "Inverse Key matrix does not exist for this key." << endl;
        found = 0;
        // exit(0);
        return;
    }
    vector<vector<int>> adj(N, vector<int>(N));
    adjoint(A, adj, N);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            inverse[i][j] = adj[i][j] * inv;
            inverse[i][j] %= 26;
        }

    // return true;
}

template <typename T>
void display(const vector<vector<T>> &mat, int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}
pair<vector<vector<int>>, vector<vector<int>>> generate()
{
    bool found = 0;
    cout << "Enter size of key matrix: ";
    cin >> n;
    pair<vector<vector<int>>, vector<vector<int>>> output;
    vector<vector<int>> key(n, vector<int>(n, 0));
    vector<vector<int>> inverse(n, vector<int>(n, 0));
    while (!found)
    {
        // cout << "Enter " << n * n << " charachters of the key: ";
        // for (int i = 0; i < n; i++)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         char c;
        //         cin >> c;
        //         key[i][j] = c - 'A';
        //     }
        // }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                key[i][j] = rand() % 26;
            }
        }
        int det = determinant(key, n);
        if (det == 0)
        {
            cout << "Not eligible for key matrix. Try again." << endl
                 << endl;
        }
        else
        {
            found = 1;
            cout << "The key is valid." << endl;
            cout << "Key matrix: " << endl;
            // for (int i = 0; i < n; i++)
            // {
            //     for (int j = 0; j < n; j++)
            //     {
            //         cout << key[i][j] << " ";
            //     }
            //     cout << endl;
            // }
            display(key, n);
            cout << endl;
            cout << "Inverse Key matrix: " << endl;
            // inverse = invert(key, n);
            invert(key, inverse, n, found);
            // for (int i = 0; i < n; i++)
            // {
            //     for (int j = 0; j < n; j++)
            //     {
            //         cout << inverse[i][j] << " ";
            //     }
            //     cout << endl;
            // }
            if (found)
                display(inverse, n);
        }
    }
    return {key, inverse};
}
vector<string> generatePartitions(string plaintext)
{
    string append((n - (plaintext.length() % n)) % n, 'Z');
    plaintext += append;
    vector<string> output;
    for (int i = 0; i < plaintext.size(); i += n)
    {
        string s(n, '.');
        for (int j = 0; j < n; j++)
        {
            s[j] = plaintext[i + j];
        }
        output.push_back(s);
    }
    return output;
}
int letterToInt(char c)
{
    return c - 'A';
}
string hill(string ele, vector<vector<int>> &key)
{
    string op(n, '.');
    // op[0] = ((key[0][0] * letterToInt(ele[0]) + key[0][1] * letterToInt(ele[1])) % 26) + 'A';
    // op[1] = ((key[1][0] * letterToInt(ele[0]) + key[1][1] * letterToInt(ele[1])) % 26) + 'A';
    for (int i = 0; i < n; i++)
    {
        int t = 0;
        for (int j = 0; j < n; j++)
        {
            t += key[i][j] * letterToInt(ele[j]);
            t %= 26;
        }
        t %= 26;
        op[i] = t + 'A';
    }
    return op;
}
string encrypt(string &plaintext, vector<vector<int>> &key)
{
    vector<string> partitions = generatePartitions(plaintext);
    string op = "";
    // cout << "Partitions before encryption: ";
    for (auto ele : partitions)
    {
        // cout << ele << " ";
        op += hill(ele, key);
    }
    return op;
}
string decrypt(string &ciphertext, vector<vector<int>> &inverseKey)
{
    vector<string> partitions = generatePartitions(ciphertext);
    string op = "";
    for (auto ele : partitions)
    {
        op += hill(ele, inverseKey);
    }
    return op;
}
int main()
{
    pair<vector<vector<int>>, vector<vector<int>>> G = generate();
    // vector<vector<int>> key = G.first;
    // vector<vector<int>> inverseKey = G.second;

    string plaintext;
    cout << "Enter the plaintext: ";
    cin >> plaintext;
    string ciphertext = encrypt(plaintext, G.first);
    cout << "The ciphertext is: " << ciphertext << endl;
    string decrypted = decrypt(ciphertext, G.second);
    cout << "The decrypted text is: " << decrypted << endl;
}