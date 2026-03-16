# 🚀 String Manipulation Library (C++)

A comprehensive **C++ String Manipulation Library** designed using Object-Oriented Programming (OOP) principles. This library provides a **dual-approach interface**, allowing for both **static (stateless)** and **instance (stateful)** string operations.

---

## ✨ Key Features

The `clsString` class includes a wide array of functionalities to handle strings efficiently:

### 🔠 Case Transformation
* **Upper/Lower Case:** Convert entire strings to all caps or all lowercase.
* **Word Capitalization:** Capitalize or decapitalize the first letter of every word.
* **Invert Case:** Swap uppercase letters to lowercase and vice versa.

### 📊 Counting & Analysis
* **Word Counter:** Count words based on space delimiters.
* **Letter Analysis:** Count total letters, or filter by capital and small letters.
* **Vowel Counter:** Detect and count vowels (`a, e, i, o, u`).
* **Specific Character:** Count occurrences of a specific letter (with case-sensitivity toggle).

### 🧹 Cleaning & Formatting
* **Trimming:** Remove leading, trailing, or all surrounding whitespace.
* **Punctuation:** Automatically strip all punctuation marks from a string.

### ⚙️ Advanced Manipulation
* **Split:** Tokenize a string into a `std::vector<string>` based on any delimiter.
* **Join:** Combine vectors or arrays of strings into a single string.
* **Reverse:** Reverse the order of words within a sentence.
* **Replace:** Swap specific words with a custom replacement string.

---

## 🛠 Implementation Details

The library follows a **Dual-Methodology** pattern:

1.  **Static Methods:** Functional-style methods that take a string as an argument and return the result. Perfect for quick, one-off utility tasks.
2.  **Instance Methods:** Operates directly on the object's internal `Value` property, maintaining state throughout the program.

> **Note:** This class utilizes the `__declspec(property)` extension (specific to MSVC) to provide a modern `Value` property for clean syntax when getting or setting the internal string.

---

## 📁 Project Structure

* **`clsString.h`**: The header-only library containing the full class definition and logic.
* **`Project4_StringLibrary.cpp`**: A robust test bench demonstrating every feature with practical examples.