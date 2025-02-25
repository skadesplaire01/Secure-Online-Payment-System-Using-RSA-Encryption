#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

// Function to perform modular exponentiation
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod; // Take mod of base
    while (exp > 0) {
        if (exp % 2 == 1) { // If exp is odd, multiply base with result
            result = (result * base) % mod;
        }
        exp = exp >> 1; // Divide exp by 2
        base = (base * base) % mod; // Square the base
    }
    return result;
}

// Function to encrypt a number using RSA
long long encrypt(long long message, long long e, long long n) {
    return modExp(message, e, n);
}

// Function to decrypt a number using RSA
long long decrypt(long long encryptedMessage, long long d, long long n) {
    return modExp(encryptedMessage, d, n);
}

// Function to encrypt a string (for cardholder name and expiry date)
std::string encryptString(const std::string& message, long long e, long long n) {
    std::string encrypted;
    for (char ch : message) {
        long long encryptedChar = encrypt(static_cast<long long>(ch), e, n);
        encrypted += std::to_string(encryptedChar) + " "; // Store encrypted values separated by spaces
    }
    return encrypted;
}

// Function to decrypt a string (for cardholder name and expiry date)
std::string decryptString(const std::string& encryptedMessage, long long d, long long n) {
    std::string decrypted;
    std::istringstream ss(encryptedMessage);
    std::string token;

    while (ss >> token) {
        long long encryptedChar = std::stoll(token);
        decrypted += static_cast<char>(decrypt(encryptedChar, d, n)); // Convert back to character
    }
    return decrypted;
}

int main() {
    // Hard-coded RSA parameters for demonstration
    long long p = 61; // prime number
    long long q = 53; // prime number
    long long n = p * q; // modulus
    long long e = 17; // public exponent (should be coprime to (p-1)(q-1))
    long long d = 2753; // private exponent

    // User input
    std::string cardHolderName;
    std::string cardNumber;
    std::string expiryDate;

    std::cout << "Enter Cardholder's Name: ";
    std::getline(std::cin, cardHolderName);
    
    std::cout << "Enter Credit Card Number: ";
    std::getline(std::cin, cardNumber); // Take card number as string for larger input
    
    std::cout << "Enter Expiry Date (MM/YY): ";
    std::getline(std::cin, expiryDate);

    // Encrypting the cardholder's name
    std::string encryptedName = encryptString(cardHolderName, e, n);
    std::cout << "Encrypted Cardholder's Name: " << encryptedName << std::endl;

    // Encrypting the card number
    std::string encryptedCard;
    for (char digit : cardNumber) {
        long long encryptedDigit = encrypt(static_cast<long long>(digit - '0'), e, n);
        encryptedCard += std::to_string(encryptedDigit) + " "; // Store encrypted digits separated by spaces
    }
    std::cout << "Encrypted Card Number: " << encryptedCard << std::endl;

    // Encrypting the expiry date
    std::string encryptedExpiryDate = encryptString(expiryDate, e, n);
    std::cout << "Encrypted Expiry Date: " << encryptedExpiryDate << std::endl;

    // Adding space for clarity
    std::cout << std::endl; // Extra space between encryption and decryption

    // Decrypting the cardholder's name
    std::string decryptedName = decryptString(encryptedName, d, n);
    std::cout << "Decrypted Cardholder's Name: " << decryptedName << std::endl;

    // Decrypting the card number
    std::string decryptedCard;
    std::istringstream ss(encryptedCard);
    std::string token;

    while (ss >> token) {
        long long encryptedDigit = std::stoll(token);
        decryptedCard += std::to_string(decrypt(encryptedDigit, d, n)); // Convert back to character
    }
    
    std::cout << "Decrypted Card Number: " << decryptedCard << std::endl;

    // Decrypting the expiry date
    std::string decryptedExpiryDate = decryptString(encryptedExpiryDate, d, n);
    std::cout << "Decrypted Expiry Date: " << decryptedExpiryDate << std::endl;

    return 0;
}
