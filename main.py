from collections import Counter
import os

def analyze_file():
    print("\n===== Dataset File Analysis =====")

    filename = input("Enter filename (example: sample1.txt): ")
    filepath = os.path.join("datasets", filename)

    try:
        with open(filepath, "r", encoding="utf-8") as file:
            text = file.read()

        characters = len(text)
        words = len(text.split())
        lines = len(text.splitlines())
        unique_characters = len(set(text))

        letters = [char.lower() for char in text if char.isalpha()]
        letter_frequency = Counter(letters)

        print("\n===== Analysis Results =====")
        print("File:", filename)
        print("Number of Characters:", characters)
        print("Number of Words:", words)
        print("Number of Lines:", lines)
        print("Number of Unique Characters:", unique_characters)

        print("\nLetter Frequency:")
        for letter in sorted(letter_frequency):
            print(letter, ":", letter_frequency[letter])

    except FileNotFoundError:
        print("\nERROR: File not found!")
        print("Make sure the file exists inside the datasets folder.")


def show_menu():
    print("\n==============================")
    print("       CryptoLabX Toolkit")
    print("==============================")
    print("1. Encrypt")
    print("2. Decrypt")
    print("3. Attack")
    print("4. Analyze")
    print("5. Exit")


def main():
    while True:
        show_menu()
        choice = input("\nEnter your choice: ")

        if choice == "1":
            print("\nEncrypt\nComing Soon")

        elif choice == "2":
            print("\nDecrypt\nComing Soon")

        elif choice == "3":
            print("\nAttack\nComing Soon")

        elif choice == "4":
            analyze_file()

        elif choice == "5":
            print("\nExiting CryptoLabX...")
            break

        else:
            print("\nInvalid choice! Please select 1, 2, 3, 4 or 5.")


if __name__ == "__main__":
    main()
