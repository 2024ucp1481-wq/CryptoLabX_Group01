
from sympy import isprime

with open("results.txt", "r") as f:
    lines = f.readlines()

prime = int(lines[1].strip())

print("========== INDEPENDENT VERIFICATION ==========")
print("Generated Number:", prime)
print("Actual Bit Length:", prime.bit_length())
print("Is 512-bit:", prime.bit_length() == 512)
print("SymPy Primality Test:", isprime(prime))

if prime.bit_length() == 512 and isprime(prime):
    print("FINAL RESULT: VERIFIED PRIME")
else:
    print("FINAL RESULT: VERIFICATION FAILED")
