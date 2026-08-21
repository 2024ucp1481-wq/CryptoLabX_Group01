import os
import sys
import csv

sys.path.insert(
    0,
    os.path.dirname(os.path.abspath(__file__))
)

from brute_force_dictionary import brute_force_dictionary
from chi_square_attack import chi_square_attack


def load_testcases(filename):
    testcases = []

    with open(filename, "r", encoding="utf-8") as file:
        for line in file:
            line = line.strip()

            if not line or line.startswith("#"):
                continue

            parts = line.split("|", 2)

            testcase_id = parts[0]
            actual_key = int(parts[1])
            ciphertext = parts[2]

            testcases.append(
                (testcase_id, actual_key, ciphertext)
            )

    return testcases


def main():
    base_dir = os.path.dirname(
        os.path.dirname(
            os.path.abspath(__file__)
        )
    )

    testcase_file = os.path.join(
        base_dir,
        "testcases",
        "testcases.txt"
    )

    dictionary_file = os.path.join(
        base_dir,
        "dictionary",
        "english_words.txt"
    )

    output_file = os.path.join(
        base_dir,
        "outputs",
        "results.csv"
    )

    testcases = load_testcases(testcase_file)

    results = []

    print("=" * 95)
    print("SHIFT CIPHER CRYPTANALYSIS")
    print("=" * 95)

    print(
        f"{'Test':<8}"
        f"{'Actual':<10}"
        f"{'Dictionary':<14}"
        f"{'Chi-Square':<14}"
        f"{'Dict Correct':<15}"
        f"{'Chi Correct':<15}"
    )

    print("-" * 95)

    for testcase_id, actual_key, ciphertext in testcases:

        dictionary_results = brute_force_dictionary(
            ciphertext,
            dictionary_file
        )

        chi_results = chi_square_attack(ciphertext)

        dictionary_key = dictionary_results[0]["key"]
        chi_key = chi_results[0]["key"]

        dictionary_correct = dictionary_key == actual_key
        chi_correct = chi_key == actual_key

        print(
            f"{testcase_id:<8}"
            f"{actual_key:<10}"
            f"{dictionary_key:<14}"
            f"{chi_key:<14}"
            f"{str(dictionary_correct):<15}"
            f"{str(chi_correct):<15}"
        )

        results.append({
            "Test Case": testcase_id,
            "Actual Key": actual_key,
            "Dictionary Key": dictionary_key,
            "Chi-Square Key": chi_key,
            "Dictionary Correct": dictionary_correct,
            "Chi-Square Correct": chi_correct,
            "Ciphertext": ciphertext,
            "Dictionary Plaintext": dictionary_results[0]["plaintext"],
            "Chi-Square Plaintext": chi_results[0]["plaintext"]
        })

    os.makedirs(
        os.path.dirname(output_file),
        exist_ok=True
    )

    with open(
        output_file,
        "w",
        newline="",
        encoding="utf-8"
    ) as file:

        fieldnames = [
            "Test Case",
            "Actual Key",
            "Dictionary Key",
            "Chi-Square Key",
            "Dictionary Correct",
            "Chi-Square Correct",
            "Ciphertext",
            "Dictionary Plaintext",
            "Chi-Square Plaintext"
        ]

        writer = csv.DictWriter(
            file,
            fieldnames=fieldnames
        )

        writer.writeheader()
        writer.writerows(results)

    print("-" * 95)
    print(f"Results saved to: {output_file}")
    print("=" * 95)


if __name__ == "__main__":
    main()
