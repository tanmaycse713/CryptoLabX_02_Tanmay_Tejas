# CryptoLabX

## Overview

CryptoLabX is a simple command-line toolkit developed for the Cryptography Laboratory course. This is the first assignment of the project. The toolkit provides a basic menu-driven interface and performs text file analysis. The encryption, decryption, and attack modules will be added in future assignments.

## Features

- Menu-driven command-line interface
- Analyze text files from the `datasets` folder
- Display:
  - Number of characters
  - Number of words
  - Number of lines
  - Number of unique characters
  - Letter frequency
- Maintain a log file (`log.txt`) with date, time, and selected menu option

## Project Structure

```
CryptoLabX/
│── datasets/
│── outputs/
│── docs/
│── tests/
│── utils/
│── classical/
│── attacks/
│── math/
│── modern/
│── analysis/
│── main.py
│── README.md
│── requirements.txt
│── log.txt
```

## Requirements

- Python 3.x

No external libraries are required. The project uses only Python's built-in modules.

## How to Run

1. Clone or download the project.
2. Open the project folder in the terminal.
3. Run the program:

```bash
python main.py
```

4. Select a menu option.
5. To use the Analyze option, place text files inside the `datasets` folder.

## Sample Menu

```
1. Encrypt
2. Decrypt
3. Attack
4. Analyze
5. Exit
```

## Team Members

- Member 1: __________________
- Member 2: __________________
- Member 3: __________________

## Future Work

In upcoming assignments, the following modules will be implemented:

- Classical Cipher Algorithms
- Modern Cryptography
- Cryptanalysis Techniques
- Encryption and Decryption
- Mathematical Utilities

## Author

Developed as part of the Cryptography Laboratory Assignment.
