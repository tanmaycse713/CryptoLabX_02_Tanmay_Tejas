def shift_encrypt(text, key):
    result = ""

    for char in text:
        if char.isalpha():
            if char.isupper():
                result += chr((ord(char) - ord('A') + key) % 26 + ord('A'))
            else:
                result += chr((ord(char) - ord('a') + key) % 26 + ord('a'))
        else:
            result += char

    return result


def shift_decrypt(text, key):

    return shift_encrypt(text, -key)


if __name__ == "__main__":
    plaintext = "HELLO WORLD"
    key = 3

    ciphertext = shift_encrypt(plaintext, key)
    decrypted = shift_decrypt(ciphertext, key)

    print("Plaintext :", plaintext)
    print("Key       :", key)
    print("Ciphertext:", ciphertext)
    print("Decrypted :", decrypted)
