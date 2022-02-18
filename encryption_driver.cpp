#include <iostream>
#include "include/aes_128_encrypt.h"
#include "include/aes_128_common.h"

using namespace std;

int main() {
    byte *key = string_to_byte_array("FLORIDAPOLYUNIV");
    bool passed = true;

    byte input[] = {
        0x41, 0x45, 0x53, 0x2d, 0x31, 0x32, 0x38, 0x20, 0x69, 0x73, 0x20, 0x67, 0x72, 0x65, 0x61, 0x74
    };

    byte expected_output[] = {
        0xef, 0x79, 0xd4, 0x0b, 0xf1, 0x61, 0x60, 0xf0, 0xd0, 0xd6, 0x9e, 0xbe, 0xe7, 0x77, 0xdf, 0xb8 
    };

    newline();
    cout << "Encryption test input: " << endl;
    print_state(input);

    newline();
    cout << "Expected output: " << endl;
    print_state(expected_output);

    byte *encrypted = encrypt_aes_128(input, key);

    newline();
    cout << "Output:" << endl;
    print_state(encrypted);
    newline();

    for (unsigned int i = 0; i < 16; i++) {
        if (encrypted[i] != expected_output[i])
            passed = false;
    }

    newline();

    if (passed)
        cout << "Test passed" << endl;
    else
        cout << "Test failed" << endl;
}