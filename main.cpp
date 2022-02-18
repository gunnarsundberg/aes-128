#include <iostream>
#include "include/aes_128_common.h"
#include "include/aes_128_encrypt.h"
#include "include/aes_128_decrypt.h"

using namespace std;

int main() {

    /**********************************************************
     * The content of this function can be completely replaced
     **********************************************************/
    byte *key = string_to_byte_array("FLORIDAPOLYUNIV");
    byte *plaintext_block = string_to_byte_array("AES-128 is great");

    //newline();
    //cout << "Key: ";
    //print_byte_array(key, 16);

    //substitute_bytes(plaintext_block);
    //print_state(plaintext_block);
    
    byte *ciphertext = encrypt_aes_128(plaintext_block, key);

    newline();
    cout << "Ciphertext:" << endl;
    print_byte_array(ciphertext, 16);

    byte *decrypted = decrypt_aes_128(ciphertext, key);

    newline();
    cout << "Decrypted text:" << endl;
    print_byte_array(decrypted, 16);

    newline();
    cout << "Plaintext:" << endl;
    for (unsigned int i = 0; i < 16; i++) {
        int val = (int) decrypted[i];
        char character = (char) val;
        cout << character;
    }

    delete key;
    delete plaintext_block;

    return 0;
}
