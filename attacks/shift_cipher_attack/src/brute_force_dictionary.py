import re
from shift_cipher import shift_decrypt


def load_dictionary(filename):
    words = set()

    with open(filename, "r") as file:
        for line in file:
            words.add(line.strip().lower())

    return words


def dictionary_score(text, dictionary):
    words = re.findall("[a-zA-Z]+", text.lower())

    score = 0

    for word in words:
        if word in dictionary:
            score += 1

    return score


def brute_force_dictionary(ciphertext, dictionary):

    results = []

    for key in range(26):
        plaintext = shift_decrypt(ciphertext, key)
        score = dictionary_score(plaintext, dictionary)

        results.append((key, plaintext, score))

    results.sort(key=lambda x: x[2], reverse=True)

    return results


# Main
dictionary = load_dictionary("../dictionary/english_words.txt")

ciphertext = "KHOOR ZRUOG"

results = brute_force_dictionary(ciphertext, dictionary)

print("Dictionary Scoring Results")
print("=" * 50)

for key, plaintext, score in results:
    print("Key:", key, "| Score:", score, "|", plaintext)

print("\nBest Result")
print("=" * 50)

print("Key      :", results[0][0])
print("Score    :", results[0][2])
print("Plaintext:", results[0][1])
