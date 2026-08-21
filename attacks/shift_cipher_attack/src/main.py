import os

from shift_cipher import shift_encrypt
from brute_force_dictionary import (
    load_dictionary,
    brute_force_dictionary
)
from chi_square_attack import chi_square_attack


def get_dictionary_result(result):
    if isinstance(result, dict):
        key = result.get("key")
        plaintext = result.get("plaintext", "")
        score = result.get("score", 0)
        return key, plaintext, score

    if isinstance(result, (tuple, list)):
        if len(result) >= 3:
            return result[0], result[1], result[2]

        if len(result) == 2:
            return result[0], result[1], 0

        if len(result) == 1:
            return result[0], "", 0

    return None, str(result), 0


def get_chi_result(result):
    if isinstance(result, dict):
        key = result.get("key")
        plaintext = result.get("plaintext", "")
        score = result.get("score", 0)
        return key, plaintext, score

    if isinstance(result, (tuple, list)):
        if len(result) >= 3:
            return result[0], result[1], result[2]

        if len(result) == 2:
            return result[0], result[1], 0

        if len(result) == 1:
            return result[0], "", 0

    return None, str(result), 0


def main():

    print("=" * 70)
    print("SHIFT CIPHER CRYPTANALYSIS")
    print("=" * 70)

    plaintext = "THIS IS A SECRET MESSAGE"
    actual_key = 5

    ciphertext = shift_encrypt(
        plaintext,
        actual_key
    )

    print("\nOriginal Plaintext:")
    print(plaintext)

    print("\nActual Key:")
    print(actual_key)

    print("\nCiphertext:")
    print(ciphertext)

    base_dir = os.path.dirname(
        os.path.dirname(
            os.path.abspath(__file__)
        )
    )

    dictionary_file = os.path.join(
        base_dir,
        "dictionary",
        "english_words.txt"
    )

    dictionary = load_dictionary(
        dictionary_file
    )

    print("\n")
    print("=" * 70)
    print("DICTIONARY SCORING ATTACK")
    print("=" * 70)

    dictionary_results = brute_force_dictionary(
        ciphertext,
        dictionary
    )

    dictionary_best_key = None
    dictionary_best_plaintext = ""
    dictionary_best_score = float("-inf")

    for result in dictionary_results:

        key, candidate_plaintext, score = get_dictionary_result(
            result
        )

        print(
            f"Key: {str(key):>2} | "
            f"Score: {score:>5} | "
            f"{candidate_plaintext}"
        )

        if score > dictionary_best_score:
            dictionary_best_score = score
            dictionary_best_key = key
            dictionary_best_plaintext = candidate_plaintext

    print("\n")
    print("=" * 70)
    print("CHI-SQUARE ATTACK")
    print("=" * 70)

    chi_results = chi_square_attack(
        ciphertext
    )

    chi_best_key = None
    chi_best_plaintext = ""
    chi_best_score = float("inf")

    for result in chi_results:

        key, candidate_plaintext, score = get_chi_result(
            result
        )

        print(
            f"Key: {str(key):>2} | "
            f"Score: {score:>10.4f} | "
            f"{candidate_plaintext}"
        )

        if score < chi_best_score:
            chi_best_score = score
            chi_best_key = key
            chi_best_plaintext = candidate_plaintext

    print("\n")
    print("=" * 70)
    print("FINAL COMPARISON")
    print("=" * 70)

    print(
        f"Actual Key          : {actual_key}"
    )

    print(
        f"Dictionary Key      : {dictionary_best_key}"
    )

    print(
        f"Dictionary Plaintext: {dictionary_best_plaintext}"
    )

    print(
        f"Dictionary Score    : {dictionary_best_score}"
    )

    print(
        f"Dictionary Correct? : "
        f"{dictionary_best_key == actual_key}"
    )

    print()

    print(
        f"Chi-Square Key      : {chi_best_key}"
    )

    print(
        f"Chi-Square Plaintext: {chi_best_plaintext}"
    )

    print(
        f"Chi-Square Score    : {chi_best_score:.4f}"
    )

    print(
        f"Chi-Square Correct? : "
        f"{chi_best_key == actual_key}"
    )


if __name__ == "__main__":
    main()
