#include "vigenere.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cmath>

using namespace std;


// =========================================================
// CLEAN CIPHERTEXT
// =========================================================

string clean_ciphertext(const string &text)
{
    string result;

    for (char ch : text)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            result += ch;
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            result += char(toupper(ch));
        }
    }

    return result;
}


// =========================================================
// FIND REPEATED PATTERNS
// =========================================================

vector<string> find_repeated_patterns(
    const string &ciphertext)
{
    vector<string> patterns;

    // Use trigrams, tetragrams and pentagrams
    for (int length = 3; length <= 5; length++)
    {
        for (int i = 0;
             i + length <= (int)ciphertext.length();
             i++)
        {
            string pattern =
                ciphertext.substr(i, length);

            bool alreadyAdded = false;

            for (string p : patterns)
            {
                if (p == pattern)
                {
                    alreadyAdded = true;
                    break;
                }
            }

            if (alreadyAdded)
                continue;

            int occurrences = 0;

            for (int j = 0;
                 j + length <= (int)ciphertext.length();
                 j++)
            {
                if (ciphertext.substr(j, length)
                    == pattern)
                {
                    occurrences++;
                }
            }

            if (occurrences >= 2)
            {
                patterns.push_back(pattern);
            }
        }
    }

    return patterns;
}


// =========================================================
// CALCULATE DISTANCES
// =========================================================

vector<int> calculate_distances(
    const string &ciphertext,
    const vector<string> &patterns)
{
    vector<int> distances;

    for (string pattern : patterns)
    {
        vector<int> positions;

        for (int i = 0;
             i + pattern.length()
             <= ciphertext.length();
             i++)
        {
            if (ciphertext.substr(
                    i,
                    pattern.length()) == pattern)
            {
                positions.push_back(i);
            }
        }

        for (int i = 1;
             i < (int)positions.size();
             i++)
        {
            distances.push_back(
                positions[i] - positions[i - 1]
            );
        }
    }

    return distances;
}


// =========================================================
// FIND FACTORS
// =========================================================

vector<int> find_factors(int distance)
{
    vector<int> factors;

    for (int i = 2; i <= distance; i++)
    {
        if (distance % i == 0)
        {
            factors.push_back(i);
        }
    }

    return factors;
}


// =========================================================
// KASISKI ANALYSIS
// =========================================================

vector<int> kasiski_analysis(
    const string &ciphertext)
{
    cout << "\n";
    cout << "========================================\n";
    cout << "KASISKI EXAMINATION\n";
    cout << "========================================\n";

    vector<string> patterns =
        find_repeated_patterns(ciphertext);

    cout << "\nRepeated patterns:\n";

    for (string pattern : patterns)
    {
        cout << pattern << "\n";
    }


    vector<int> distances =
        calculate_distances(
            ciphertext,
            patterns
        );


    cout << "\nDistances:\n";

    for (int d : distances)
    {
        cout << d << " ";
    }

    cout << "\n";


    // Count candidate key lengths
    int votes[101] = {0};

    for (int distance : distances)
    {
        vector<int> factors =
            find_factors(distance);

        for (int factor : factors)
        {
            if (factor <= 100)
            {
                votes[factor]++;
            }
        }
    }


    vector<pair<int, int>> candidates;

    for (int i = 2; i <= 20; i++)
    {
        if (votes[i] > 0)
        {
            candidates.push_back(
                {i, votes[i]}
            );
        }
    }


    sort(
        candidates.begin(),
        candidates.end(),
        [](pair<int, int> a,
           pair<int, int> b)
        {
            return a.second > b.second;
        }
    );


    cout << "\nCandidate key lengths:\n";

    for (auto candidate : candidates)
    {
        cout << "Length "
             << candidate.first
             << " -> "
             << candidate.second
             << " votes\n";
    }


    vector<int> result;

    for (auto candidate : candidates)
    {
        result.push_back(candidate.first);

        if (result.size() == 5)
            break;
    }

    return result;
}


// =========================================================
// INDEX OF COINCIDENCE
// =========================================================

double calculate_ic(
    const string &text)
{
    int count[26] = {0};

    int N = 0;

    for (char ch : text)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            count[ch - 'A']++;
            N++;
        }
    }

    if (N <= 1)
        return 0.0;

    double numerator = 0;

    for (int i = 0; i < 26; i++)
    {
        numerator +=
            count[i] * (count[i] - 1);
    }

    double denominator =
        N * (N - 1);

    return numerator / denominator;
}


// =========================================================
// SPLIT INTO GROUPS
// =========================================================

vector<string> split_into_groups(
    const string &ciphertext,
    int keyLength)
{
    vector<string> groups(
        keyLength,
        ""
    );

    for (int i = 0;
         i < (int)ciphertext.length();
         i++)
    {
        groups[i % keyLength] +=
            ciphertext[i];
    }

    return groups;
}


// =========================================================
// FREQUENCY ANALYSIS
// =========================================================

void frequency_analysis(
    const vector<string> &groups)
{
    cout << "\n";
    cout << "========================================\n";
    cout << "FREQUENCY ANALYSIS FOR EACH GROUP\n";
    cout << "========================================\n";


    for (int g = 0;
         g < (int)groups.size();
         g++)
    {
        cout << "\nGroup "
             << g + 1
             << ":\n";

        int count[26] = {0};

        int total =
            groups[g].length();


        for (char ch : groups[g])
        {
            count[ch - 'A']++;
        }


        cout << left
             << setw(8)
             << "Letter"
             << setw(8)
             << "Count"
             << "Percentage\n";

        cout << "-----------------------------\n";


        for (int i = 0; i < 26; i++)
        {
            double percentage = 0;

            if (total > 0)
            {
                percentage =
                    count[i] * 100.0 / total;
            }

            cout << char('A' + i)
                 << "\t"
                 << count[i]
                 << "\t"
                 << fixed
                 << setprecision(2)
                 << percentage
                 << "%\n";
        }


        cout << "IC = "
             << fixed
             << setprecision(4)
             << calculate_ic(groups[g])
             << "\n";
    }
}


// =========================================================
// FIND CAESAR SHIFT
// =========================================================

int find_shift(
    const string &group)
{
    // English letter frequency
    double english[26] =
    {
        8.167, 1.492, 2.782, 4.253,
        12.702, 2.228, 2.015, 6.094,
        6.966, 0.153, 0.772, 4.025,
        2.406, 6.749, 7.507, 1.929,
        0.095, 5.987, 6.327, 9.056,
        2.758, 0.978, 2.360, 0.150,
        1.974, 0.074
    };


    int observed[26] = {0};

    for (char ch : group)
    {
        observed[ch - 'A']++;
    }


    int N = group.length();

    double bestChiSquare = 1e100;

    int bestShift = 0;


    for (int shift = 0;
         shift < 26;
         shift++)
    {
        double chiSquare = 0;


        for (int i = 0; i < 26; i++)
        {
            int cipherIndex =
                (i + shift) % 26;

            double expected =
                N * english[i] / 100.0;

            double actual =
                observed[cipherIndex];


            if (expected > 0)
            {
                chiSquare +=
                    (actual - expected)
                    *
                    (actual - expected)
                    / expected;
            }
        }


        if (chiSquare < bestChiSquare)
        {
            bestChiSquare = chiSquare;
            bestShift = shift;
        }
    }


    return bestShift;
}


// =========================================================
// FIND KEY
// =========================================================

string find_key(
    const vector<string> &groups)
{
    string key = "";

    cout << "\n";
    cout << "========================================\n";
    cout << "PROBABLE KEY\n";
    cout << "========================================\n";


    for (int i = 0;
         i < (int)groups.size();
         i++)
    {
        int shift =
            find_shift(groups[i]);


        char keyChar =
            'A' + shift;


        key += keyChar;


        cout << "Group "
             << i + 1
             << " -> Shift "
             << shift
             << " -> Key letter "
             << keyChar
             << "\n";
    }


    cout << "\nRecovered key: "
         << key
         << "\n";


    return key;
}


// =========================================================
// VIGENERE DECRYPT
// =========================================================

string vigenere_decrypt(
    const string &ciphertext,
    const string &key)
{
    string plaintext = "";

    for (int i = 0;
         i < (int)ciphertext.length();
         i++)
    {
        int cipherValue =
            ciphertext[i] - 'A';

        int keyValue =
            key[i % key.length()] - 'A';

        int plainValue =
            (cipherValue - keyValue + 26)
            % 26;

        plaintext +=
            char('A' + plainValue);
    }

    return plaintext;
}


// =========================================================
// VIGENERE ENCRYPT
// =========================================================

string vigenere_encrypt(
    const string &plaintext,
    const string &key)
{
    string ciphertext = "";

    for (int i = 0;
         i < (int)plaintext.length();
         i++)
    {
        int plainValue =
            plaintext[i] - 'A';

        int keyValue =
            key[i % key.length()] - 'A';

        int cipherValue =
            (plainValue + keyValue)
            % 26;

        ciphertext +=
            char('A' + cipherValue);
    }

    return ciphertext;
}


// =========================================================
// VERIFY
// =========================================================

bool verify(
    const string &originalCiphertext,
    const string &plaintext,
    const string &key)
{
    string generated =
        vigenere_encrypt(
            plaintext,
            key
        );

    return generated ==
           originalCiphertext;
}