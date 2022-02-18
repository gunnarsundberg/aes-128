#include <iostream>
#include "include/aes_128_key_expansion.h"
#include "include/aes_128_common.h"

using namespace std;

int main() {
    bool passed = true;

    byte *input = string_to_byte_array("FLORIDAPOLYUNIV");
    byte expected_output[] = {
        0x46, 0x49, 0x4f, 0x4e, 0x4c, 0x44, 0x4c, 0x49, 0x4f, 0x41, 0x59, 0x56, 0x52, 0x50, 0x55, 0x00,
        0x7c, 0x35, 0x7a, 0x34, 0xfd, 0xb9, 0xf5, 0xbc, 0x2c, 0x6d, 0x34, 0x62, 0x7d, 0x2d, 0x78, 0x78,
        0x1b, 0x2e, 0x54, 0x60, 0x57, 0xee, 0x1b, 0xa7, 0x90, 0xfd, 0xc9, 0xab, 0x65, 0x48, 0x30, 0x48,
        0x43, 0x6d, 0x39, 0x59, 0x35, 0xdb, 0xc0, 0x67, 0xc2, 0x3f, 0xf6, 0x5d, 0xb5, 0xfd, 0xcd, 0x85,
        0xce, 0xa3, 0x9a, 0xc3, 0x79, 0xa2, 0x62, 0x05, 0x55, 0x6a, 0x9c, 0xc1, 0x7e, 0x83, 0x4e, 0xcb,
        0xb5, 0x16, 0x8c, 0x4f, 0x01, 0xa3, 0xc1, 0xc4, 0x4a, 0x20, 0xbc, 0x7d, 0x50, 0xd3, 0x9d, 0x56,
        0x89, 0x9f, 0x13, 0x5c, 0xfe, 0x5d, 0x9c, 0x58, 0xfb, 0xdb, 0x67, 0x1a, 0xd4, 0x07, 0x9a, 0xcc,
        0xa3, 0x3c, 0x2f, 0x73, 0x5c, 0x01, 0x9d, 0xc5, 0xb0, 0x6b, 0x0c, 0x16, 0x9e, 0x99, 0x03, 0xcf,
        0x85, 0xb9, 0x96, 0xe5, 0x1b, 0x1a, 0x87, 0x42, 0x3a, 0x51, 0x5d, 0x4b, 0x11, 0x88, 0x8b, 0x44,
        0xb2, 0x0b, 0x9d, 0x78, 0xa8, 0xb2, 0x35, 0x77, 0x21, 0x70, 0x2d, 0x66, 0xc8, 0x40, 0xcb, 0x8f,
        0x71, 0x7a, 0xe7, 0x9f, 0x9b, 0x29, 0x1c, 0x6b, 0x52, 0x22, 0x0f, 0x69, 0x74, 0x34, 0xff, 0x70
    };

    newline();
    cout << "Key expansion test input: " << endl;
    print_byte_array(input, 16);

    newline();
    cout << "Expected output: " << endl;
    for (unsigned int i = 0; i < 10; i++) {
        print_byte_array(&expected_output[16*i], 16);
    }

    byte *round_key = new byte[16];
    byte expanded_key[176];

    // Copy key to expanded key and transpose
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            expanded_key[i*4 + j] = input[j*4 + i];
        }
    }

    // Copy first 16 bytes of extended key to round_key
    for (unsigned int i = 0; i < 16; i++){
        round_key[i] = expanded_key[i];
    }

    newline();
    cout << "Initial key: " << endl;
    print_byte_array(round_key, 16);

    // Perform key expansion and store all round keys in expanded_key
    for (int i = 1; i < 11; i++) {
        round_key = get_round_key(round_key, i);
        for(unsigned int j = 0; j < 16; j++) {
            expanded_key[16*i + j] = round_key[j];
        }

        newline();
        cout << "Round " << i << " key: " << endl;
        print_byte_array(round_key, 16);
	}

    newline();
    cout << "Output: " << endl;
    for (unsigned int i = 0; i < 10; i++) {
        print_byte_array(&expanded_key[16*i], 16);
    }

    newline();

    for (unsigned int i = 0; i < 176; i++) {
        if (expanded_key[i] != expected_output[i])
            passed = false;
    }

    newline();
    
    if (passed)
        cout << "Test passed" << endl;
    else
        cout << "Test failed" << endl;

}