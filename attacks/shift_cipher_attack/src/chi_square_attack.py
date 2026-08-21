from shift_cipher import shift_decrypt


ENGLISH_FREQUENCIES = {
    'a': 8.167,
    'b': 1.492,
    'c': 2.782,
    'd': 4.253,
    'e': 12.702,
    'f': 2.228,
    'g': 2.015,
    'h': 6.094,
    'i': 6.966,
    'j': 0.153,
    'k': 0.772,
    'l': 4.025,
    'm': 2.406,
    'n': 6.749,
    'o': 7.507,
    'p': 1.929,
    'q': 0.095,
    'r': 5.987,
    's': 6.327,
    't': 9.056,
    'u': 2.758,
    'v': 0.978,
    'w': 2.360,
    'x': 0.150,
    'y': 1.974,
    'z': 0.074
}


def chi_square_score(text):
    letters = [
        char.lower()
        for char in text
        if char.isalpha()
    ]

    total = len(letters)

    if total == 0:
        return float("inf")

    counts = {}

    for letter in ENGLISH_FREQUENCIES:
        counts[letter] = 0

    for letter in letters:
        counts[letter] += 1

    score = 0.0

    for letter, frequency in ENGLISH_FREQUENCIES.items():
        expected = total * frequency / 100
        observed = counts[letter]

        if expected > 0:
            score += ((observed - expected) ** 2) / expected

    return score


def chi_square_attack(ciphertext):
    results = []

    for key in range(26):
        plaintext = shift_decrypt(ciphertext, key)
        score = chi_square_score(plaintext)

        results.append({
            "key": key,
            "plaintext": plaintext,
            "score": score
        })

    results.sort(key=lambda x: x["score"])

    return results


if __name__ == "__main__":
    ciphertext = "WKH TXLFN EURZQ IRA MXPSV RYHU WKH ODCB GRJ"

    results = chi_square_attack(ciphertext)

    print("Chi-Square Analysis Results")
    print("=" * 70)

    for result in results:
        print(
            f"Key: {result['key']:2d} | "
            f"Chi-Square: {result['score']:.4f} | "
            f"{result['plaintext']}"
        )
