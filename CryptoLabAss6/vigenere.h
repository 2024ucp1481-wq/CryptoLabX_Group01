#ifndef VIGENERE_H
#define VIGENERE_H

#include <string>
#include <vector>
#include <map>

using namespace std;

string clean_ciphertext(const string &text);

vector<string> find_repeated_patterns(const string &ciphertext);

vector<int> calculate_distances(
    const string &ciphertext,
    const vector<string> &patterns
);

vector<int> find_factors(int distance);

vector<int> kasiski_analysis(
    const string &ciphertext
);

double calculate_ic(
    const string &text
);

vector<string> split_into_groups(
    const string &ciphertext,
    int keyLength
);

void frequency_analysis(
    const vector<string> &groups
);

int find_shift(
    const string &group
);

string find_key(
    const vector<string> &groups
);

string vigenere_decrypt(
    const string &ciphertext,
    const string &key
);

string vigenere_encrypt(
    const string &plaintext,
    const string &key
);

bool verify(
    const string &originalCiphertext,
    const string &plaintext,
    const string &key
);

#endif