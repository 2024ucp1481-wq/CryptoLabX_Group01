#include "cipher.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;


// ---------------------------------------------------------
// Generate substitution key
// ---------------------------------------------------------
void generate_key(string &key)
{
    key = "QWERTYUIOPASDFGHJKLZXCVBNM";

    cout << "\nSubstitution Key:\n";
    cout << "Plain : ABCDEFGHIJKLMNOPQRSTUVWXYZ\n";
    cout << "Cipher: " << key << "\n";
}


// ---------------------------------------------------------
// Apply substitution
// ---------------------------------------------------------
string apply_substitution(const string &text, const string &key)
{
    string result = text;

    for (int i = 0; i < (int)text.length(); i++)
    {
        char ch = text[i];

        if (ch >= 'A' && ch <= 'Z')
        {
            result[i] = key[ch - 'A'];
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            result[i] = tolower(key[ch - 'a']);
        }
        else
        {
            result[i] = ch;
        }
    }

    return result;
}


// ---------------------------------------------------------
// Frequency Analysis
// ---------------------------------------------------------
void frequency_analysis(
    const string &ciphertext,
    vector<pair<char, int>> &frequency)
{
    int count[26] = {0};

    int totalLetters = 0;

    for (char ch : ciphertext)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            count[ch - 'A']++;
            totalLetters++;
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            count[ch - 'a']++;
            totalLetters++;
        }
    }

    frequency.clear();

    for (int i = 0; i < 26; i++)
    {
        frequency.push_back({'A' + i, count[i]});
    }

    sort(
        frequency.begin(),
        frequency.end(),
        [](const pair<char, int> &a,
           const pair<char, int> &b)
        {
            return a.second > b.second;
        }
    );

    cout << "\n========================================\n";
    cout << "LETTER FREQUENCY ANALYSIS\n";
    cout << "========================================\n";

    cout << left
         << setw(10) << "Letter"
         << setw(10) << "Count"
         << setw(15) << "Percentage"
         << "\n";

    cout << "----------------------------------------\n";

    for (auto p : frequency)
    {
        double percentage = 0;

        if (totalLetters != 0)
        {
            percentage =
                (double)p.second * 100.0 / totalLetters;
        }

        cout << left
             << setw(10) << p.first
             << setw(10) << p.second
             << fixed << setprecision(2)
             << percentage << "%\n";
    }

    cout << "\nMost frequent ciphertext letters:\n";

    int shown = 0;

    for (auto p : frequency)
    {
        if (p.second > 0 && shown < 5)
        {
            cout << p.first << " -> "
                 << p.second << " occurrences\n";

            shown++;
        }
    }
}


// ---------------------------------------------------------
// Word Frequency Analysis
// ---------------------------------------------------------
void word_frequency_analysis(const string &ciphertext)
{
    vector<string> words;

    string current = "";

    for (char ch : ciphertext)
    {
        if (isalpha(ch))
        {
            current += tolower(ch);
        }
        else
        {
            if (!current.empty())
            {
                words.push_back(current);
                current = "";
            }
        }
    }

    if (!current.empty())
        words.push_back(current);


    vector<pair<string, int>> frequencies;

    for (string word : words)
    {
        bool found = false;

        for (auto &p : frequencies)
        {
            if (p.first == word)
            {
                p.second++;
                found = true;
                break;
            }
        }

        if (!found)
        {
            frequencies.push_back({word, 1});
        }
    }


    sort(
        frequencies.begin(),
        frequencies.end(),
        [](const pair<string, int> &a,
           const pair<string, int> &b)
        {
            return a.second > b.second;
        }
    );


    cout << "\n========================================\n";
    cout << "WORD FREQUENCY ANALYSIS\n";
    cout << "========================================\n";


    cout << "\nOne-letter words:\n";

    for (auto p : frequencies)
    {
        if (p.first.length() == 1)
        {
            cout << p.first
                 << " -> "
                 << p.second << "\n";
        }
    }


    cout << "\nTwo-letter words:\n";

    for (auto p : frequencies)
    {
        if (p.first.length() == 2)
        {
            cout << p.first
                 << " -> "
                 << p.second << "\n";
        }
    }


    cout << "\nThree-letter words:\n";

    for (auto p : frequencies)
    {
        if (p.first.length() == 3)
        {
            cout << p.first
                 << " -> "
                 << p.second << "\n";
        }
    }


    cout << "\nRepeated words:\n";

    for (auto p : frequencies)
    {
        if (p.second > 1)
        {
            cout << p.first
                 << " -> "
                 << p.second << " times\n";
        }
    }
}


// ---------------------------------------------------------
// Pattern Analysis
// ---------------------------------------------------------
string getPattern(const string &word)
{
    int mapping[26];

    for (int i = 0; i < 26; i++)
        mapping[i] = -1;

    int nextNumber = 0;

    string pattern = "";

    for (char ch : word)
    {
        int index = ch - 'a';

        if (mapping[index] == -1)
        {
            mapping[index] = nextNumber++;
        }

        pattern += char('0' + mapping[index]);
    }

    return pattern;
}


void pattern_analysis(const string &ciphertext)
{
    vector<string> words;

    string current = "";

    for (char ch : ciphertext)
    {
        if (isalpha(ch))
        {
            current += tolower(ch);
        }
        else
        {
            if (!current.empty())
            {
                words.push_back(current);
                current = "";
            }
        }
    }

    if (!current.empty())
        words.push_back(current);


    cout << "\n========================================\n";
    cout << "WORD PATTERN ANALYSIS\n";
    cout << "========================================\n";


    for (string word : words)
    {
        if (word.length() >= 2)
        {
            cout << left
                 << setw(15)
                 << word
                 << " Pattern: "
                 << getPattern(word)
                 << "\n";
        }
    }
}


// ---------------------------------------------------------
// Display Partial Plaintext
// ---------------------------------------------------------
string display_partial_plaintext(
    const string &ciphertext,
    const string &key)
{
    string result = ciphertext;

    for (int i = 0; i < (int)ciphertext.length(); i++)
    {
        char ch = ciphertext[i];

        if (ch >= 'A' && ch <= 'Z')
        {
            char plain = '?';

            for (int j = 0; j < 26; j++)
            {
                if (key[j] == ch)
                {
                    plain = 'A' + j;
                    break;
                }
            }

            result[i] = plain;
        }
        else if (ch >= 'a' && ch <= 'z')
        {
            char upper = toupper(ch);

            char plain = '?';

            for (int j = 0; j < 26; j++)
            {
                if (key[j] == upper)
                {
                    plain = 'a' + j;
                    break;
                }
            }

            result[i] = plain;
        }
        else
        {
            result[i] = ch;
        }
    }

    cout << "\n========================================\n";
    cout << "PARTIAL PLAINTEXT\n";
    cout << "========================================\n";

    cout << result << "\n";

    return result;
}


// ---------------------------------------------------------
// Verify Solution
// ---------------------------------------------------------
bool verify_solution(
    const string &plaintext,
    const string &ciphertext,
    const string &key)
{
    string generatedCipher =
        apply_substitution(plaintext, key);

    if (generatedCipher == ciphertext)
    {
        return true;
    }

    return false;
}