import random
import string

def cipher(data, seed):
    random.seed(seed)
    out = bytearray()
    for b in data:
        if isinstance(b, str):
            b = ord(b)
        out.append(b ^ random.randint(0, 255))
    return bytes(out)

test_msg = b"Hello Crypto"
test_ct = cipher(test_msg, 9999)
test_dt = cipher(test_ct, 9999)
print("Test Decrypt:", test_dt)

prefix_len = random.randint(5, 20)
prefix = ''.join(random.choices(string.printable[:94], k=prefix_len))
plaintext = (prefix + "A" * 14).encode()

secret_seed = random.randint(0, 65535)
ciphertext = cipher(plaintext, secret_seed)

print("Original Plaintext:", plaintext)
print("Ciphertext (hex):", ciphertext.hex())

for s in range(65536):
    decrypted = cipher(ciphertext, s)
    if b"AAAAAAAAAAAAAA" in decrypted:
        print("Recovered Seed:", s)
        print("Recovered Plaintext:", decrypted)
        break
