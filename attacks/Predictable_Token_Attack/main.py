import random
import time

T = int(time.time())
random.seed(T)
token_bytes = bytearray()
for _ in range(16):
    token_bytes.append(random.randint(0, 255))
token = token_bytes.hex()

print("Timestamp T:", T)
print("Token:", token)

tested = 0
recovered_T = None

for t in range(T - 300, T + 301):
    tested += 1
    random.seed(t)
    cand_bytes = bytearray()
    for _ in range(16):
        cand_bytes.append(random.randint(0, 255))
    
    if cand_bytes.hex() == token:
        recovered_T = t
        break

print("Timestamps Tested:", tested)
print("Recovered Timestamp:", recovered_T)

if recovered_T:
    random.seed(recovered_T)
    verify_bytes = bytearray()
    for _ in range(16):
        verify_bytes.append(random.randint(0, 255))
    print("Verified Token:", verify_bytes.hex())
