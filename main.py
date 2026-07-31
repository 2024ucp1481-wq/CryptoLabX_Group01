import os
from datetime import datetime
from collections import Counter

LOG_FILE = "outputs/log.txt"

os.makedirs("outputs", exist_ok=True)


def log_option(option):
    with open(LOG_FILE, "a") as f:
        f.write(f"{datetime.now()} --> {option}\n")


def analyze_file():

    filename = input("Enter file name (example: sample1.txt): ")

    path = os.path.join("datasets", filename)

    if not os.path.exists(path):
        print("File not found")
        return

    with open(path, "r") as file:
        text = file.read()

    characters = len(text)
    words = len(text.split())
    lines = len(text.splitlines())
    unique_characters = len(set(text))

    letters = [c.lower() for c in text if c.isalpha()]
    frequency = Counter(letters)

    print("\nAnalysis")
    print("----------------------")
    print("Characters :", characters)
    print("Words :", words)
    print("Lines :", lines)
    print("Unique Characters :", unique_characters)

    print("\nLetter Frequency")

    for letter in sorted(frequency):
        print(letter, ":", frequency[letter])


while True:

    print("\n====== CryptoLabX ======")
    print("1. Encrypt")
    print("2. Decrypt")
    print("3. Attack")
    print("4. Analyze")
    print("5. Exit")

    choice = input("Enter choice: ")

    if choice == "1":
        log_option("Encrypt")
        print("Coming Soon")

    elif choice == "2":
        log_option("Decrypt")
        print("Coming Soon")

    elif choice == "3":
        log_option("Attack")
        print("Coming Soon")

    elif choice == "4":
        log_option("Analyze")
        analyze_file()

    elif choice == "5":
        log_option("Exit")
        print("Good Bye")
        break

    else:
        print("Invalid Choice")