#include <iostream>
#include <string>

using namespace std;

// Simple encryption function (Caesar Cipher)
string encrypt(string data, int key) {
    string encryptedData = "";
    for (int i = 0; i < data.length(); i++) {
        encryptedData += char(int(data[i]) + key); // Shift character by key
    }
    return encryptedData;
}

// Simple decryption function (Caesar Cipher)
string decrypt(string data, int key) {
    string decryptedData = "";
    for (int i = 0; i < data.length(); i++) {
        decryptedData += char(int(data[i]) - key); // Shift character back by key
    }
    return decryptedData;
}

class PaymentSystem {
private:
    string cardNumber;
    string cvv;
    string expiryDate;
    string cardHolderName;
    const int encryptionKey = 5;  // Key for encryption

public:
    // Function to capture user input
    void getCardDetails() {
        cout << "Enter Card Holder Name: ";
        getline(cin, cardHolderName);
        cout << "Enter Card Number: ";
        getline(cin, cardNumber);
        cout << "Enter CVV: ";
        getline(cin, cvv);
        cout << "Enter Expiry Date (MM/YY): ";
        getline(cin, expiryDate);
        
        // Encrypt sensitive data
        cardNumber = encrypt(cardNumber, encryptionKey);
        cvv = encrypt(cvv, encryptionKey);
        expiryDate = encrypt(expiryDate, encryptionKey);

        cout << "\nPayment details have been securely encrypted.\n";
    }

    // Function to process payment (Dummy function for simulation)
    void processPayment() {
        cout << "\nProcessing payment for " << cardHolderName << "...\n";
        cout << "Encrypted Card Number: " << cardNumber << "\n";
        cout << "Encrypted CVV: " << cvv << "\n";
        cout << "Encrypted Expiry Date: " << expiryDate << "\n";
        
        // Decrypt data for processing
        string decryptedCardNumber = decrypt(cardNumber, encryptionKey);
        string decryptedCVV = decrypt(cvv, encryptionKey);
        string decryptedExpiryDate = decrypt(expiryDate, encryptionKey);

        cout << "\nPayment processed successfully!\n";
        cout << "Decrypted Card Number: " << decryptedCardNumber << "\n";
        cout << "Decrypted CVV: " << decryptedCVV << "\n";
        cout << "Decrypted Expiry Date: " << decryptedExpiryDate << "\n";
    }
};

int main() {
    PaymentSystem payment;

    // Get payment details
    payment.getCardDetails();

    // Process the payment
    payment.processPayment();

    return 0;
}
