import random
import time

def mr_test(num, rounds=40):
    if num in (2, 3):
        return True
    if num <= 1 or num % 2 == 0:
        return False

    s = 0
    d = num - 1
    while d % 2 == 0:
        d //= 2
        s += 1

    for _ in range(rounds):
        a = random.randrange(2, num - 1)
        x = pow(a, d, num)
        
        if x == 1 or x == num - 1:
            continue
            
        for _ in range(s - 1):
            x = pow(x, 2, num)
            if x == num - 1:
                break
        else:
            return False
            
    return True

def get_prime(bit_size):
    start = time.time()
    count = 0

    while True:
        count += 1
        val = random.getrandbits(bit_size)
        val |= (1 << (bit_size - 1)) | 1
        
        if mr_test(val, 40):
            return val, count, time.time() - start

def fermat_check(n):
    return pow(2, n - 1, n) == 1 and pow(3, n - 1, n) == 1

target_bits = 512
p, attempts, time_taken = get_prime(target_bits)
actual = p.bit_length()

print("EXPERIMENTAL RESULTS:")
print("Assigned length:", target_bits)
print("Generated candidate:\n", p)
print("Actual bit length:", actual)
print("Candidates tested:", attempts)
print("Miller-Rabin rounds: 40")
print(f"Total time: {time_taken:.4f} seconds")
print()

print("VERIFICATION:")
print(f"Length correct? {actual == target_bits}")
print(f"MSB check ((p >> 511) == 1)? {(p >> 511) == 1}")
print("Miller-Rabin passed? Yes (40 rounds)")
print("Fermat test (base 2 & 3):", "PASS" if fermat_check(p) else "FAIL")
