## MegaCalc

## Overview
MegaCalc is a high-precision calculator developed in Standard C++ with support for complex arithmetic operations, large numbers (up to 2560 bits), and various mathematical functions. This project leverages the GMP library to perform efficient large number calculations and provides a wide range of mathematical features such as modulus operations, exponentiation, and root calculations.

## Features
- **Mixed Arithmetic:** Supports addition, subtraction, multiplication, and division with large numbers.
- **Mathematical Functions:** Includes functions for absolute value (ABS), square root (SQRT), and Pi (π).
- **Modulus Operations:** Perform modulus calculations with high precision.
- **Exponentiation and Root Calculations:** Compute powers and roots of numbers.
- **Support for Large Numbers:** Handle numbers up to 2560 bits in size using the GMP library.

## Prerequisites
Before using MegaCalc, make sure you have the following installed:
- **MinGW**: Development suite for compiling the C++ program.
- **MSYS**: Auxiliary environment for working with MinGW.
- **GMP Library**: GMP (GNU Multiple Precision Arithmetic Library) for large number calculations.

## Installation

### Step 1: Install MinGW
Download and install the MinGW development suite from the QT official website.

### Step 2: Install MSYS
Download and install MSYS for setting up the development environment.

### Step 3: Install GMP Library
1. Download the GMP library from the official website.
2. Extract the files to the root directory of your C drive (or any directory of your choice).
3. Compile the library:
   ```bash
   cd /path/to/gmp
   ./configure --enable-cxx
   make
   make check
   make install

### Compile MegaCalc
g++ -Wall -o Calculator Calculator.cpp icon.o -lgmpxx -lgmp

### Run
./Calculator

