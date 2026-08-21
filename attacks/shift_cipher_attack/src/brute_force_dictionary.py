import re
import os

from shift_cipher import shift_decrypt


def load_dictionary(dictionary_file):
    words = set()

    with open(dictionary_file, "r", encoding="utf-8") as file:
        for line in file:
            word = line.strip().lower()

            if word:
                words.add(word)

    return words


def dictionary_score(text, dictionary):
    words = re.findall(r"[a-zA-Z]+", text.lower())

    if not words:
        return 0

    matched = sum(1 for word in words if word in dictionary)

    return matched


def brute_force_dictionary(ciphertext, dictionary_file):
    dictionary = load_dictionary(dictionary_file)

    results = []

    for key in range(26):
        plaintext = shift_decrypt(ciphertext, key)
        score = dictionary_score(plaintext, dictionary)

        results.append({
            "key": key,
            "plaintext": plaintext,
            "score": score
        })

    results.sort(
        key=lambda x: (x["score"], len(x["plaintext"])),
        reverse=True
    )

    return results


if __name__ == "__main__":
    base_dir = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

    dictionary_file = os.path.join(
        base_dir,
        "dictionary",
        "english_words.txt"
    )

    ciphertext = "WKH TXLFN EURZQ IRA MXPSV RYHU WKH ODCB GRJ"

    results = brute_force_dictionary(
        ciphertext,
        dictionary_file
    )

    print("Dictionary Scoring Results")
    print("=" * 70)

    for result in results:
        print(
            f"Key: {result['key']:2d} | "
            f"Score: {result['score']:2d} | "
            f"{result['plaintext']}"
        )
