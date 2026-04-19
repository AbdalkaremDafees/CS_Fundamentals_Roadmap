# 🚀 Date & String Utility Library (C++)

A comprehensive **C++ Date and String Utility Library** built using Object-Oriented Programming (OOP) principles. This library provides a **dual-approach interface**, allowing for both **static (stateless)** and **instance (stateful)** operations for complex date calculations and advanced string processing.

---

## ✨ Key Features

The library consists of two robust classes, `clsDate` and `clsString`, designed to handle data efficiently:

### 📅 Date Manipulation (`clsDate`)
* **Flexible Initialization:** Multiple constructors to initialize dates from system time, specific "dd/mm/yyyy" strings, or day-order within a year.
* **Date Arithmetic:** Support for adding or subtracting days, weeks, months, years, decades, and centuries.
* **Calendar Generation:** Functions to print professionally formatted monthly and yearly calendars directly to the console.
* **Business Logic:** Specialized methods to calculate business days, weekend status, and vacation return dates.
* **Validation:** Reliable logic for leap year detection and date validity checks.

### 🔠 String Processing (`clsString`)
* **Case Transformation:** Convert strings to upper/lower case, capitalize first letters of words, or invert the case of all characters.
* **Counting & Analysis:** Count words, vowels, and specific letters, or perform case-sensitive analysis.
* **Cleaning & Formatting:** Advanced trimming (Left, Right, Both) and automated punctuation removal.
* **Advanced Manipulation:** Tokenize strings into vectors based on delimiters or join them back together.

---

## 🛠 Implementation Details

The library follows a **Dual-Methodology** pattern for maximum developer flexibility:

1.  **Static Methods:** Functional-style utility methods that accept external arguments and return results immediately without modifying object state.
2.  **Instance Methods:** Stateful operations that work directly on the object's internal data members.

> **Note:** This library utilizes the `__declspec(property)` extension (specific to MSVC) to provide a modern `Day`, `Month`, `Year`, and `Value` property syntax for clean code.

---

## 📁 Project Structure

* **`clsDate.h`**: The header-only library containing the complete `clsDate` class and Gregorian algorithms.
* **`clsString.h`**: A robust utility header for string manipulation and tokenization.
* **`Project5_DateLibrary.cpp`**: A comprehensive test bench demonstrating multiple constructors and library functions.

---