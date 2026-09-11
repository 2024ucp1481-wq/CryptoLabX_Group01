#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "vigenere.h"

using namespace std;


// =========================================================
// READ FILE
// =========================================================

string read_file(
    const string &filename)
{
    ifstream file(filename);

    if (!file)
    {
        cout << "Error opening file: "
             << filename
             << "\n";

        return "";
    }


    string text;
    string line;


    while (getline(file, line))
    {
        text += line;
        text += '\n';
    }


    file.close();

    return text;
}


// =========================================================
// WRITE FILE
// =========================================================

void write_file(
    const string &filename,
    const string &text)
{
    ofstream file(filename);

    file << text;

    file.close();
}


// =========================================================
// MAIN
// =========================================================

int main()
{
    cout << "========================================\n";
    cout << "VIGENERE CIPHER CRYPTANALYSIS\n";
    cout << "KASISKI EXAMINATION + FREQUENCY ANALYSIS\n";
    cout << "========================================\n";


    // -----------------------------------------------------
    // STEP 1
    // -----------------------------------------------------

    string rawCiphertext =
        read_file("ciphertext.txt");


    if (rawCiphertext.empty())
    {
        cout << "Ciphertext file is empty.\n";
        return 0;
    }


    string ciphertext =
        clean_ciphertext(
            rawCiphertext
        );


    cout << "\nCiphertext preprocessing completed.\n";

    cout << "Total ciphertext letters: "
         << ciphertext.length()
         << "\n";


    // -----------------------------------------------------
    // STEP 2
    // KASISKI ANALYSIS
    // -----------------------------------------------------

    vector<int> candidates =
        kasiski_analysis(
            ciphertext
        );


    if (candidates.empty())
    {
        cout << "\nKasiski test did not produce candidates.\n";
        return 0;
    }


    // -----------------------------------------------------
    // STEP 3
    // Select best candidate
    // -----------------------------------------------------

    int estimatedKeyLength =
        candidates[0];


    cout << "\n";
    cout << "========================================\n";
    cout << "ESTIMATED KEY LENGTH\n";
    cout << "========================================\n";

    cout << "Estimated key length = "
         << estimatedKeyLength
         << "\n";


    // -----------------------------------------------------
    // STEP 4
    // Split ciphertext
    // -----------------------------------------------------

    vector<string> groups =
        split_into_groups(
            ciphertext,
            estimatedKeyLength
        );


    cout << "\nCiphertext divided into "
         << groups.size()
         << " groups.\n";


    // -----------------------------------------------------
    // STEP 5
    // Frequency analysis
    // -----------------------------------------------------

    frequency_analysis(
        groups
    );


    // -----------------------------------------------------
    // STEP 6
    // Find key
    // -----------------------------------------------------

    string key =
        find_key(
            groups
        );


    // -----------------------------------------------------
    // STEP 7
    // Decrypt
    // -----------------------------------------------------

    string plaintext =
        vigenere_decrypt(
            ciphertext,
            key
        );


    write_file(
        "recovered_plaintext.txt",
        plaintext
    );


    cout << "\n";
    cout << "========================================\n";
    cout << "RECOVERED PLAINTEXT\n";
    cout << "========================================\n";

    cout << plaintext
         << "\n";


    // -----------------------------------------------------
    // STEP 8
    // Verification
    // -----------------------------------------------------

    bool result =
        verify(
            ciphertext,
            plaintext,
            key
        );


    cout << "\n";
    cout << "========================================\n";
    cout << "VERIFICATION\n";
    cout << "========================================\n";


    if (result)
    {
        cout << "SUCCESS!\n";
        cout << "Re-encrypted ciphertext matches the original ciphertext.\n";
    }
    else
    {
        cout << "FAILED!\n";
        cout << "Recovered key/plaintext is not correct.\n";
    }


    cout << "\n";
    cout << "========================================\n";
    cout << "PROGRAM COMPLETED\n";
    cout << "========================================\n";


    return 0;
}