VIGENERE CIPHER CRYPTANALYSIS

Language:
C++

Technique:
Kasiski Examination and Frequency Analysis

Files:

1. main.cpp
2. vigenere.cpp
3. vigenere.h
4. ciphertext.txt
5. recovered_plaintext.txt

Functions:

1. clean_ciphertext()
2. find_repeated_patterns()
3. calculate_distances()
4. find_factors()
5. kasiski_analysis()
6. calculate_ic()
7. split_into_groups()
8. frequency_analysis()
9. find_shift()
10. find_key()
11. vigenere_decrypt()
12. vigenere_encrypt()
13. verify()

Compilation:
g++ -std=c++17 main.cpp vigenere.cpp -o vigenere

Execution:
.\vigenere.exe

The program preprocesses the given Vigenère ciphertext, estimates the key length using Kasiski examination, divides the ciphertext into groups, performs frequency analysis, determines probable Caesar shifts, recovers the Vigenère key, decrypts the ciphertext and verifies the solution through re-encryption.
