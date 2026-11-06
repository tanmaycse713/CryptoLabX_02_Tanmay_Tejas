import numpy as np
import scipy.stats as stats
import math

def analyze_rng_data(filepath):
    print(f"--- Analyzing: {filepath} ---")
    
    with open(filepath, 'rb') as f:
        data = f.read()
    
    bytes_data = np.frombuffer(data, dtype=np.uint8)
    
    observed_freq, _ = np.histogram(bytes_data, bins=256, range=(0, 256))
    expected_freq = [len(bytes_data) / 256] * 256
    chi2_stat, p_value = stats.chisquare(observed_freq, expected_freq)
    
    print(f"Byte Chi-Square Statistic: {chi2_stat:.4f}")
    print(f"Byte Chi-Square p-value: {p_value:.4f}")
    
    if p_value < 0.01:
        print("Result: FAILED")
    else:
        print("Result: PASSED")
        
    total_bits = len(bytes_data) * 8
    ones_count = sum(bin(byte).count('1') for byte in bytes_data)
    ones_ratio = ones_count / total_bits
    
    print(f"Bit Distribution: {ones_ratio:.4%} Ones, {1-ones_ratio:.4%} Zeros")
    
    x = bytes_data[:-1]
    y = bytes_data[1:]
    correlation, _ = stats.pearsonr(x, y)
    print(f"Serial Correlation Coefficient (Lag 1): {correlation:.6f}")
    
    probabilities = observed_freq / len(bytes_data)
    entropy = -sum(p * math.log2(p) for p in probabilities if p > 0)
    print(f"Shannon Entropy: {entropy:.6f}\n")

analyze_rng_data("urandom_data.bin")
analyze_rng_data("openssl_data.bin")
analyze_rng_data("windows_cng_data.bin")
