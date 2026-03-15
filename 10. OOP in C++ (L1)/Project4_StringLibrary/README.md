String Manipulation Library (C++)
This project is a comprehensive C++ String Manipulation Library designed using Object-Oriented Programming (OOP) principles. It provides a dual-approach interface, allowing users to perform operations either through static methods (stateless) or object-level methods (stateful).

The library simplifies common string tasks such as word counting, case conversion, trimming, splitting, and joining, making it a robust utility for C++ developers.

Key Features
The clsString class includes a wide array of functionalities:

Case Transformation:

Convert entire strings to Upper/Lower case.

Capitalize or decapitalize the first letter of every word.

Invert the case of all characters in a string.

Counting & Analysis:

Count words based on space delimiters.

Count total letters, small letters, or capital letters specifically.

Count vowels (a, e, i, o, u) and occurrences of specific characters.

Cleaning & Formatting:

Trimming: Remove leading, trailing, or both sets of whitespace.

Punctuation: Remove all punctuation marks from a string.

Advanced Manipulation:

Split: Tokenize a string into a std::vector<string> based on a delimiter.

Join: Combine a vector or an array of strings into a single string with a custom delimiter.

Reverse: Reverse the order of words within a sentence.

Replace: Replace specific words with custom logic (supports Case Sensitivity toggle).

Implementation Details
The library is built with a Dual-Methodology pattern:

Static Methods: Functional-style methods that take a string as an argument and return the result. Ideal for quick, one-off operations.

Instance Methods: Operates on the internal _Value property of the clsString object, providing a more state-persistent approach.

Note: The class utilizes the __declspec(property) extension (specific to MSVC) to provide a convenient Value property for getting and setting the internal string.

Project Structure
clsString.h: The header-only library containing the class definition and all method logic.

Project4_StringLibrary.cpp: A comprehensive test bench demonstrating every feature of the library.