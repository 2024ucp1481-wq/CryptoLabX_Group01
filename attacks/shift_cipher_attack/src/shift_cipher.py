def shift_encrypt(text, key):
    result = ""

    for char in text:
        if char.isalpha():
            base = ord('A') if char.isupper() else ord('a')
            result += chr((ord(char) - base + key) % 26 + base)
        else:
            result += char

    return result


def shift_decrypt(text, key):
    return shift_encrypt(text, -key)


if __name__ == "__main__":
    plaintext = "THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG"
    key = 3

    ciphertext = shift_encrypt(plaintext, key)
    decrypted = shift_decrypt(ciphertext, key)

    print("Plaintext :", plaintext)
    print("Key       :", key)
    print("Ciphertext:", ciphertext)
    print("Decrypted :", decrypted)
