
import numpy as np
import secrets
import string
import time
from datetime import datetime, timezone

# MT19937 Stream Cipher

def stream_cipher(data, seed):
    rng = np.random.RandomState(seed)
    output = bytearray()

    for byte in data:
        key = int(rng.randint(0, 256))
        output.append(byte ^ key)

    return bytes(output)


print("\n========== PART A: STREAM CIPHER ==========")

# Basic encryption and decryption
test_message = b"Hello Cryptography Lab"
test_seed = 12345

encrypted = stream_cipher(test_message, test_seed)
decrypted = stream_cipher(encrypted, test_seed)

print("Original Message:", test_message.decode())
print("Encrypted Ciphertext:", encrypted.hex())
print("Decrypted Message:", decrypted.decode())
print("Encryption-Decryption Verified:", test_message == decrypted)


# Generate random prefix followed by 14 A's
prefix_length = secrets.randbelow(16) + 5
prefix = ''.join(
    secrets.choice(string.ascii_letters + string.digits)
    for _ in range(prefix_length)
)

plaintext = (prefix + "A" * 14).encode()
secret_seed = secrets.randbelow(65536)

ciphertext = stream_cipher(plaintext, secret_seed)

print("\n--- Known Plaintext Attack ---")
print("Plaintext:", plaintext.decode())
print("Ciphertext:", ciphertext.hex())
print("Actual 16-bit Seed:", secret_seed)

# Brute-force all 65536 seeds
start = time.perf_counter()

recovered_seed = None
recovered_plaintext = None

for seed in range(65536):
    candidate = stream_cipher(ciphertext, seed)
    if b"A" * 14 in candidate:
        recovered_seed = seed
        recovered_plaintext = candidate
        break

end = time.perf_counter()

print("Recovered Seed:", recovered_seed)
print("Recovered Plaintext:", recovered_plaintext.decode())
print("Candidates Tested:", recovered_seed + 1)
print("Seed Recovery Time:", round(end - start, 6), "seconds")
print("Seed Match:", recovered_seed == secret_seed)
print("Complete Plaintext Verified:",
      recovered_plaintext == plaintext)
print("Known Sequence Verified:",
      b"A" * 14 in recovered_plaintext)


# Part B: Predictable Password Reset Tokens

print("\n========== PART B: RESET TOKEN ATTACK ==========")

# Generate token using current Unix timestamp
timestamp = int(time.time())

def generate_token(seed):
    rng = np.random.RandomState(seed)
    token = bytearray()

    for _ in range(16):
        token.append(int(rng.randint(0, 256)))

    return bytes(token)


observed_token = generate_token(timestamp)

print("Generation Timestamp:", timestamp)
print("Generation Date:", datetime.fromtimestamp(
    timestamp, timezone.utc))
print("Generated Token:", observed_token.hex())

# Attacker searches timestamp +/- 300 seconds
start_time = timestamp - 300
end_time = timestamp + 300

start = time.perf_counter()

recovered_timestamp = None
tested = 0

for candidate_time in range(start_time, end_time + 1):
    tested += 1
    candidate_token = generate_token(candidate_time)

    if candidate_token == observed_token:
        recovered_timestamp = candidate_time
        break

end = time.perf_counter()

print("\n--- Timestamp Prediction Attack ---")
print("Search Interval:", start_time, "to", end_time)
print("Total Candidates Tested:", tested)
print("Recovered Timestamp:", recovered_timestamp)
print("Timestamp Match:", recovered_timestamp == timestamp)

# Regenerate token using recovered timestamp
verified_token = generate_token(recovered_timestamp)

print("Regenerated Token:", verified_token.hex())
print("Token Verification:", verified_token == observed_token)

# Save all experimental results
with open("results.txt", "w") as f:
    f.write("ASSIGNMENT 10: MT19937\n\n")

    f.write("PART A: STREAM CIPHER\n")
    f.write("Test Message: " + test_message.decode() + "\n")
    f.write("Test Ciphertext: " + encrypted.hex() + "\n")
    f.write("Decrypted Message: " + decrypted.decode() + "\n")
    f.write("Encryption Verified: " + str(test_message == decrypted) + "\n\n")

    f.write("Plaintext: " + plaintext.decode() + "\n")
    f.write("Ciphertext: " + ciphertext.hex() + "\n")
    f.write("Actual Seed: " + str(secret_seed) + "\n")
    f.write("Recovered Seed: " + str(recovered_seed) + "\n")
    f.write("Candidates Tested: " + str(recovered_seed + 1) + "\n")
    f.write("Recovered Plaintext: " + recovered_plaintext.decode() + "\n")
    f.write("Complete Plaintext Verified: " + str(recovered_plaintext == plaintext) + "\n\n")

    f.write("PART B: TIMESTAMP TOKEN ATTACK\n")
    f.write("Generation Timestamp: " + str(timestamp) + "\n")
    f.write("Generated Token: " + observed_token.hex() + "\n")
    f.write("Search Interval: " + str(start_time) + " to " + str(end_time) + "\n")
    f.write("Candidates Tested: " + str(tested) + "\n")
    f.write("Recovered Timestamp: " + str(recovered_timestamp) + "\n")
    f.write("Regenerated Token: " + verified_token.hex() + "\n")
    f.write("Token Verified: " + str(verified_token == observed_token) + "\n")

print("\nAll results saved in results.txt")
