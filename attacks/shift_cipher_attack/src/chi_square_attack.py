from collections import Counter
from shift_cipher import shift_decrypt


ENGLISH_FREQUENCIES = {
    'a': 0.08167,
    'b': 0.01492,
    'c': 0.02782,
    'd': 0.04253,
    'e': 0.12702,
    'f': 0.02228,
    'g': 0.02015,
    'h': 0.06094,
    'i': 0.06966,
    'j': 0.00153,
    'k': 0.00772,
    'l': 0.04025,
    'm': 0.02406,
    'n': 0.06749,
    'o': 0.07507,
    'p': 0.01929,
    'q': 0.00095,
    'r': 0.05987,
    's': 0.06327,
    't': 0.09056,
    'u': 0.02758,
    'v': 0.00978,
    'w': 0.02360,
    'x': 0.00150,
    'y': 0.01974,
    'z': 0.00074
}


def chi_square_score(text):
    """
    Calculate the Chi-Square statistic between
    observed letter frequencies and expected
    English frequencies.
    """

    letters = [
        char.lower()
        for char in text
        if char.isalpha()
    ]

    total = len(letters)

    if total == 0:
        return float("inf")

    counts = Counter(letters)

    chi_square = 0.0

    for letter in "abcdefghijklmnopqrstuvwxyz":

        observed = counts.get(letter, 0)

        expected = (
            ENGLISH_FREQUENCIES[letter] * total
        )

        if expected > 0:
            chi_square += (
                (observed - expected) ** 2
            ) / expected

    return chi_square


def chi_square_attack(ciphertext):

    results = []

    for key in range(26):

        plaintext = shift_decrypt(
            ciphertext,
            key
        )

        score = chi_square_score(
            plaintext
        )

        results.append({
            "key": key,
            "plaintext": plaintext,
            "score": score
        })

    results.sort(
        key=lambda x: x["score"]
    )

    return results


if __name__ == "__main__":

    ciphertext = "KHOOR ZRUOG"

    results = chi_square_attack(
        ciphertext
    )

    print("\nChi-Square Results")
    print("=" * 70)

    for result in results:

        print(
            f"Key: {result['key']:2d} | "
            f"Chi-Square: {result['score']:.4f} | "
            f"{result['plaintext']}"
        )

    print("\nBest Result")
    print("=" * 70)

    print("Key       :", results[0]["key"])
    print("Score     :", results[0]["score"])
    print("Plaintext :", results[0]["plaintext"])
