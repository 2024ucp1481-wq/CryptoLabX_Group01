
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

from scipy.stats import chisquare, binomtest, pearsonr, norm
from pathlib import Path

DATA_DIR = Path("data")
RESULT_DIR = Path("results")

RESULT_DIR.mkdir(exist_ok=True)

files = {
    "Linux /dev/urandom": DATA_DIR / "linux_urandom.bin",
    "OpenSSL rand": DATA_DIR / "openssl.bin",
    "Windows CNG": DATA_DIR / "windows_cng.bin"
}

results = []
frequency_data = {}

for name, path in files.items():

    data = path.read_bytes()

    print("\nAnalyzing:", name)

    print("File Size:", len(data), "bytes")

    if len(data) < 1048576:
        raise ValueError("File must contain at least 1 MB")

    arr = np.frombuffer(data, dtype=np.uint8)

    # Byte frequency distribution
    freq = np.bincount(arr, minlength=256)
    frequency_data[name] = freq

    chi_stat, chi_p = chisquare(freq)

    # Bit distribution
    bits = np.unpackbits(arr)
    ones = int(np.sum(bits))
    zeros = len(bits) - ones

    bit_p = binomtest(
        ones, n=len(bits), p=0.5
    ).pvalue

    # Repeated adjacent bytes
    repeated_bytes = int(
        np.sum(arr[:-1] == arr[1:])
    )

    # Repeated 4-byte blocks
    blocks = [
        data[i:i+4]
        for i in range(0, len(data)-3, 4)
    ]

    repeated_blocks = len(blocks) - len(set(blocks))

    # Serial correlation
    correlation, correlation_p = pearsonr(
        arr[:-1], arr[1:]
    )

    # Runs test on bits
    runs = 1 + int(np.sum(bits[:-1] != bits[1:]))

    n0 = zeros
    n1 = ones
    n = n0 + n1

    mean_runs = (2 * n0 * n1) / n + 1

    variance = (
        2 * n0 * n1 * (2 * n0 * n1 - n0 - n1)
        / (n * n * (n - 1))
    )

    z = (runs - mean_runs) / np.sqrt(variance)
    runs_p = 2 * norm.sf(abs(z))

    results.append({
        "Generator": name,
        "Size (bytes)": len(data),
        "Byte Chi-square p-value": chi_p,
        "Bit Ones (%)": ones / n * 100,
        "Bit Balance p-value": bit_p,
        "Repeated Adjacent Bytes": repeated_bytes,
        "Repeated 4-byte Blocks": repeated_blocks,
        "Serial Correlation": correlation,
        "Serial Correlation p-value": correlation_p,
        "Runs Test p-value": runs_p
    })

    print("Byte Chi-square p-value:", chi_p)
    print("Bit Ones:", ones)
    print("Bit Zeros:", zeros)
    print("Bit Balance p-value:", bit_p)
    print("Repeated Adjacent Bytes:", repeated_bytes)
    print("Repeated 4-byte Blocks:", repeated_blocks)
    print("Serial Correlation:", correlation)
    print("Runs Test p-value:", runs_p)

# Save statistical results
df = pd.DataFrame(results)

df.to_csv(
    RESULT_DIR / "statistical_results.csv",
    index=False
)

print("\n========== FINAL COMPARISON ==========")
print(df.to_string(index=False))

# Save byte frequency table
frequency_df = pd.DataFrame(frequency_data)
frequency_df.index.name = "Byte Value"

frequency_df.to_csv(
    RESULT_DIR / "byte_frequencies.csv"
)

# Plot byte frequency distributions
plt.figure(figsize=(12, 5))

for name, freq in frequency_data.items():
    plt.plot(range(256), freq, label=name)

plt.xlabel("Byte Value")
plt.ylabel("Frequency")
plt.title("Byte Frequency Distribution")
plt.legend()
plt.tight_layout()

plt.savefig(RESULT_DIR / "byte_frequency.png")
plt.show()

print("\nAll analysis results saved successfully.")
