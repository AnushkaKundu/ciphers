#include <bits/stdc++.h>
using namespace std;

string readfile(string inputFileName)
{
    ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
    {
        std::cerr << "Error opening file: " << inputFileName << std::endl;
    }

    string fileContent((std::istreambuf_iterator<char>(inputFile)),
                       std::istreambuf_iterator<char>());
    return fileContent;
}

void writeToFile(string outputFileName, string fileContent)
{
    ofstream outputFile(outputFileName);
    if (!outputFile.is_open())
    {
        std::cerr << "Error opening file: " << outputFileName << std::endl;
    }

    outputFile << fileContent;
}

void encryptChar(char &c, int shift)
{
    if (c == 32 || c == 44 || c == 46)
        return;
    int i = c - 'A';
    i += shift;
    i %= 26;
    c = 'A' + i;
    return;
}

string encrypt(string text, int shift)
{
    for (auto &ele : text)
    {
        encryptChar(ele, shift);
    }
    return text;
}

string decryptWithKnownShift(string text, int shift)
{
    text = encrypt(text, 26 - shift);
    return text;
}

int findShift(int s)
{
    return (s - 69 + 26) % 26;
}

string decryptWithFrequencyAnalysis(string text)
{
    vector<int> frequency(26, 0);
    int maxFreqIdx = 0;
    for (auto ele : text)
    {
        if (ele == 32 || ele == 44 || ele == 46)
            continue;
        frequency[ele - 'A']++;
        // cout << frequency[ele - 'A'] << " ";
        if (frequency[maxFreqIdx] < frequency[ele - 'A'])
            maxFreqIdx = ele - 'A';
    }
    int shift = findShift(maxFreqIdx + 'A');
    return decryptWithKnownShift(text, shift);
}

int main()
{
    int shift = 3;

    string inputStr = readfile("test.txt");
    cout << "The plain text file: " << endl
         << inputStr << endl
         << endl;

    string encryptedString = encrypt(inputStr, shift);
    writeToFile("encrypted.txt", encryptedString);
    cout << "The file after encryption: " << endl
         << encryptedString << endl
         << endl;

    string decryptedStringWithKnownShift = decryptWithKnownShift(encryptedString, shift);
    writeToFile("decryptedWithKnownShift.txt", decryptedStringWithKnownShift);
    cout << "The file after decryption with known shift value: " << endl
         << decryptedStringWithKnownShift << endl
         << endl;

    string decryptedStringWithFrequencyAnalysis = decryptWithFrequencyAnalysis(encryptedString);
    writeToFile("decryptedWithFrequencyAnalysis.txt", decryptedStringWithFrequencyAnalysis);
    cout << "The file after decryption with frequency analysis: " << endl
         << decryptedStringWithFrequencyAnalysis << endl
         << endl;

    return 0;
}