
import secrets
import time

BASES = [2, 3, 5, 7, 11, 13, 17, 19,
         23, 29, 31, 37, 41, 43, 47, 53]

ROUNDS = len(BASES)
BITS = 512


def miller_rabin(n, bases):
    if n < 2:
        return False

    if n in (2, 3):
        return True

    if n % 2 == 0:
        return False

    d = n - 1
    s = 0

    while d % 2 == 0:
        d //= 2
        s += 1

    for a in bases:
        if a >= n:
            continue

        x = pow(a, d, n)

        if x == 1 or x == n - 1:
            continue

        for _ in range(s - 1):
            x = pow(x, 2, n)

            if x == n - 1:
                break
        else:
            return False

    return True


def generate_candidate():
    n = secrets.randbits(BITS)
    n |= (1 << (BITS - 1))
    n |= 1
    return n


def main():
    count = 0
    start = time.perf_counter()

    while True:
        candidate = generate_candidate()
        count += 1

        if miller_rabin(candidate, BASES):
            break

    end = time.perf_counter()

    print("\n========== MILLER-RABIN RESULTS ==========")
    print("Generated Prime:")
    print(candidate)
    print("\nHexadecimal:")
    print(hex(candidate))
    print("\nAssigned Bit Length:", BITS)
    print("Actual Bit Length:", candidate.bit_length())
    print("Number of Candidates Tested:", count)
    print("Number of Miller-Rabin Rounds:", ROUNDS)
    print("Bases Used:", BASES)
    print("Total Execution Time:", round(end - start, 6), "seconds")

    print("\n========== VERIFICATION ==========")
    print("Exact 512-bit check:",
          candidate.bit_length() == BITS)
    print("Miller-Rabin verification:",
          miller_rabin(candidate, BASES))

    with open("results.txt", "w") as f:
        f.write("Generated Prime:\n")
        f.write(str(candidate) + "\n\n")
        f.write("Hexadecimal:\n")
        f.write(hex(candidate) + "\n\n")
        f.write("Assigned Bit Length: 512\n")
        f.write("Actual Bit Length: " +
                str(candidate.bit_length()) + "\n")
        f.write("Candidates Tested: " + str(count) + "\n")
        f.write("Miller-Rabin Rounds: " + str(ROUNDS) + "\n")
        f.write("Bases Used: " + str(BASES) + "\n")
        f.write("Execution Time: " +
                str(round(end - start, 6)) + " seconds\n")


if __name__ == "__main__":
    main()
