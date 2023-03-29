#include <iostream>
#include <string>

// Define a UDL for binary literals, using the suffix "_b"
constexpr int operator ""_b(unsigned long long x) {
    return x + 1;
}

int main() {
    // Use the binary UDL to define an integer value
    int value = 101010_b;

    // Print the value in decimal
    std::cout << value << std::endl;

    return 0;
}