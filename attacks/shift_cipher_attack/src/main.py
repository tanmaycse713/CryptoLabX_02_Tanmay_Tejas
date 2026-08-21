import os

from shift_cipher import shift_encrypt
from brute_force_dictionary import (
    load_dictionary,
    brute_force_dictionary
)
from chi_square_attack import chi_square_attack


def main():

    print("=" * 70)
    print("SHIFT CIPHER CRYPTANALYSIS")
    print("=" * 70)

    # --------------------------------------------------
    # Original plaintext and key
    # --------------------------------------------------

    plaintext = "THIS IS A SECRET MESSAGE"

    actual_key = 5

    # --------------------------------------------------
    # Encrypt
    # --------------------------------------------------

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

    # --------------------------------------------------
    # Load dictionary
    # --------------------------------------------------

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

    # --------------------------------------------------
    # Dictionary Attack
    # --------------------------------------------------

    print("\n")
    print("=" * 70)
    print("DICTIONARY SCORING ATTACK")
    print("=" * 70)

    dictionary_results = brute_force_dictionary(
        ciphertext,
        dictionary
    )

    for result in dictionary_results:

        print(
            f"Key: {result['key']:2d} | "
            f"Score: {result['score']:2d} | "
            f"{result['plaintext']}"
        )

    dictionary_key = dictionary_results[0]["key"]

    # --------------------------------------------------
    # Chi-Square Attack
    # --------------------------------------------------

    print("\n")
    print("=" * 70)
    print("CHI-SQUARE ATTACK")
    print("=" * 70)

    chi_results = chi_square_attack(
        ciphertext
    )

    for result in chi_results:

        print(
            f"Key: {result['key']:2d} | "
            f"Score: {result['score']:.4f} | "
            f"{result['plaintext']}"
        )

    chi_square_key = chi_results[0]["key"]

    # --------------------------------------------------
    # Final Comparison
    # --------------------------------------------------

    print("\n")
    print("=" * 70)
    print("FINAL COMPARISON")
    print("=" * 70)

    print(
        f"Actual Key          : {actual_key}"
    )

    print(
        f"Dictionary Key      : {dictionary_key}"
    )

    print(
        f"Chi-Square Key      : {chi_square_key}"
    )

    print(
        f"Dictionary Correct? : "
        f"{dictionary_key == actual_key}"
    )

    print(
        f"Chi-Square Correct? : "
        f"{chi_square_key == actual_key}"
    )


if __name__ == "__main__":
    main()
