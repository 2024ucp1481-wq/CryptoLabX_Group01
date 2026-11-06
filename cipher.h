#ifndef CIPHER_H
#define CIPHER_H

#include <string>
#include <vector>

using namespace std;

void generate_key(string &key);

string apply_substitution(const string &text, const string &key);

void frequency_analysis(
    const string &ciphertext,
    vector<pair<char, int>> &frequency
);

void word_frequency_analysis(const string &ciphertext);

void pattern_analysis(const string &ciphertext);

string display_partial_plaintext(
    const string &ciphertext,
    const string &key
);

bool verify_solution(
    const string &plaintext,
    const string &ciphertext,
    const string &key
);

#endif