MONOALPHABETIC SUBSTITUTION CIPHER AND CRYPTANALYSIS

Language:
C++

Files:

1. main.cpp
2. cipher.cpp
3. cipher.h
4. plaintext.txt
5. ciphertext.txt
6. recovered_plaintext.txt

Functions Implemented:

1. frequency_analysis()
2. word_frequency_analysis()
3. pattern_analysis()
4. apply_substitution()
5. display_partial_plaintext()
6. verify_solution()

Compilation Command:
g++ -std=c++17 main.cpp cipher.cpp -o crypto

Execution Command:
.\crypto.exe

The program implements monoalphabetic substitution encryption and performs frequency, word-frequency and pattern analysis. The recovered substitution is validated by re-encrypting the recovered plaintext and comparing the generated ciphertext with the original ciphertext.
