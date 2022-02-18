#include "../include/aes_128_encrypt.h"
#include "../include/aes_128_common.h"
#include "../include/aes_128_key_expansion.h"

// Encryption function
byte* encrypt_aes_128(byte* plaintext, byte* key) {
	byte *ciphertext = new byte[16];
	byte *round_key = new byte[16];

	// Copy ciphertext to plaintext
	for (unsigned int i = 0; i < 16; i++) {
        ciphertext[i] = plaintext[i];
	}

	// Copy and transpose key
	for (unsigned int i = 0; i < 4; i++) {
        for (unsigned int j = 0; j < 4; j++) {
            round_key[i*4 + j] = key[j*4 + i];
        }
    }

	// Initial round key
	add_round_key(round_key, ciphertext);
	
	// Rounds 1-9
	for (int i = 1; i < 10; i++) {
		substitute_bytes(ciphertext);
		shift_rows(ciphertext);
		mix_columns(ciphertext);
		round_key = get_round_key(round_key, i);
		add_round_key(round_key, ciphertext);
	}

	// Final Round
	substitute_bytes(ciphertext);
	shift_rows(ciphertext);
	round_key = get_round_key(round_key, 10);
	add_round_key(round_key, ciphertext);

	return ciphertext;
}

// Shift rows
void shift_rows(byte* byte_array) {
    byte *temp = new byte[16];

	// Row 1
	temp[0] = byte_array[0];
	temp[1] = byte_array[1];
	temp[2] = byte_array[2];
	temp[3] = byte_array[3];

	// Row 2
	temp[4] = byte_array[5];
	temp[5] = byte_array[6];
	temp[6] = byte_array[7];
	temp[7] = byte_array[4];

	// Row 3
	temp[8] = byte_array[10];
	temp[9] = byte_array[11];
	temp[10] = byte_array[8];
	temp[11] = byte_array[9];

	// Row 4
	temp[12] = byte_array[15];
	temp[13] = byte_array[12];
	temp[14] = byte_array[13];
	temp[15] = byte_array[14];

	for (int i = 0; i < 16; i++) {
		byte_array[i] = temp[i];
	}

}

// Mix Columns
void mix_columns(byte* byte_array) {
	byte *temp = new byte[16];
	
	for (unsigned int i = 0; i < 4; i++) {
		temp[i] = gf_mul_2[byte_array[i]] ^ gf_mul_3[byte_array[i + 4]] ^ byte_array[i + 8] ^ byte_array[i + 12];
	}

	for (unsigned int i = 0; i < 4; i++) {
		temp[i+4] = byte_array[i] ^ gf_mul_2[byte_array[i + 4]] ^ gf_mul_3[byte_array[i + 8]] ^ byte_array[i + 12];
	}

	for (unsigned int i = 0; i < 4; i++) {
		temp[i+8] = byte_array[i] ^  byte_array[i + 4] ^ gf_mul_2[byte_array[i + 8]] ^ gf_mul_3[byte_array[i + 12]];
	}

	for (unsigned int i = 0; i < 4; i++) {
		temp[i+12] = gf_mul_3[byte_array[i]] ^ byte_array[i + 4] ^  byte_array[i + 8] ^ gf_mul_2[byte_array[i + 12]];
	}

	for (int i = 0; i < 16; i++) {
		byte_array[i] = temp[i];
	}
}
