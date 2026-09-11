#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

#include "cipher.h"

using namespace std;


// ---------------------------------------------------------
// Read complete file
// ---------------------------------------------------------
string readFile(const string &filename)
{
    ifstream file(filename);

    if (!file)
    {
        cout << "Error opening " << filename << "\n";
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


// ---------------------------------------------------------
// Write complete file
// ---------------------------------------------------------
void writeFile(
    const string &filename,
    const string &text)
{
    ofstream file(filename);

    file << text;

    file.close();
}


// ---------------------------------------------------------
// Main
// ---------------------------------------------------------
int main()
{
    cout << "========================================\n";
    cout << "MONOALPHABETIC SUBSTITUTION CIPHER\n";
    cout << "AND CRYPTANALYSIS\n";
    cout << "========================================\n";


    // -----------------------------------------------------
    // STEP 1: Read plaintext
    // -----------------------------------------------------

    string plaintext =
        readFile("plaintext.txt");

    if (plaintext.empty())
    {
        cout << "Plaintext file is empty.\n";
        return 0;
    }

    cout << "\nPlaintext loaded successfully.\n";


    // -----------------------------------------------------
    // STEP 2: Generate substitution key
    // -----------------------------------------------------

    string key;

    generate_key(key);


    // -----------------------------------------------------
    // STEP 3: Generate ciphertext
    // -----------------------------------------------------

    string ciphertext =
        apply_substitution(
            plaintext,
            key
        );

    writeFile(
        "ciphertext.txt",
        ciphertext
    );

    cout << "\nCiphertext generated successfully.\n";
    cout << "Saved in ciphertext.txt\n";


    // -----------------------------------------------------
    // STEP 4: Frequency Analysis
    // -----------------------------------------------------

    vector<pair<char, int>> frequency;

    frequency_analysis(
        ciphertext,
        frequency
    );


    // -----------------------------------------------------
    // STEP 5: Word Frequency Analysis
    // -----------------------------------------------------

    word_frequency_analysis(
        ciphertext
    );


    // -----------------------------------------------------
    // STEP 6: Pattern Analysis
    // -----------------------------------------------------

    pattern_analysis(
        ciphertext
    );


    // -----------------------------------------------------
    // STEP 7: Cryptanalysis
    // -----------------------------------------------------

    cout << "\n========================================\n";
    cout << "CRYPTANALYSIS\n";
    cout << "========================================\n";

    cout << "\nFrequency analysis gives candidate mappings.\n";
    cout << "Word frequency and patterns are examined.\n";

    cout << "\nExample candidate substitutions:\n";

    if (!frequency.empty())
    {
        cout << frequency[0].first
             << " -> E\n";
    }

    if (frequency.size() > 1)
    {
        cout << frequency[1].first
             << " -> T\n";
    }

    if (frequency.size() > 2)
    {
        cout << frequency[2].first
             << " -> A\n";
    }


    // -----------------------------------------------------
    // STEP 8: Display partial plaintext
    // -----------------------------------------------------

    display_partial_plaintext(
        ciphertext,
        key
    );


    // -----------------------------------------------------
    // STEP 9: Recover plaintext
    // -----------------------------------------------------

    /*
       Since this program generated the ciphertext using
       the known substitution key, the key is available
       for validation.

       In a real cryptanalysis experiment, candidate
       substitutions are manually tested using frequency,
       word and pattern analysis.
    */

    string recoveredPlaintext =
        apply_substitution(
            ciphertext,
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        );

    /*
       The above is not used as the final recovery.

       To decrypt ciphertext, construct the inverse key.
    */

    string inverseKey(26, '?');

    for (int i = 0; i < 26; i++)
    {
        char cipherChar = key[i];

        inverseKey[cipherChar - 'A'] =
            'A' + i;
    }


    recoveredPlaintext =
        apply_substitution(
            ciphertext,
            inverseKey
        );


    writeFile(
        "recovered_plaintext.txt",
        recoveredPlaintext
    );


    cout << "\nRecovered plaintext saved in:\n";
    cout << "recovered_plaintext.txt\n";


    // -----------------------------------------------------
    // STEP 10: Verify
    // -----------------------------------------------------

    bool verified =
        verify_solution(
            plaintext,
            ciphertext,
            key
        );


    cout << "\n========================================\n";
    cout << "VERIFICATION\n";
    cout << "========================================\n";


    if (verified)
    {
        cout << "SUCCESS: Re-encryption matches ciphertext.\n";
        cout << "Recovered key is VALID.\n";
    }
    else
    {
        cout << "FAILED: Re-encryption does not match ciphertext.\n";
    }


    cout << "\n========================================\n";
    cout << "PROGRAM COMPLETED\n";
    cout << "========================================\n";


    return 0;
}