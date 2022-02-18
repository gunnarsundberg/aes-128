#include "../include/aes_128_key_expansion.h"
#include "../include/aes_128_common.h"

// Circular Left Shift (Rotate Left)
void circular_left_shift(byte *byte_word) {
	byte *temp = new byte[4];
	
	// Shift bytes
	temp[0] = byte_word[1];
	temp[1] = byte_word[2];
	temp[2] = byte_word[3];
	temp[3] = byte_word[0];
	
	// Copy values to byte_word
	for (unsigned int i = 0; i < 4; i++) {
		byte_word[i] = temp[i];
	}
}

// Add Round Constant
void add_round_constant(byte *byte_word, unsigned char round_number) {
    byte_word[0] = byte_word[0] ^ rcon_table[round_number];
}


// The g function of the AES key expansion
byte *g_function(byte *byte_word)
{
    byte *g_return_word = new byte[4];
    
	// S box
	for (unsigned int i = 0; i < 4; i++) {
		g_return_word[i] = substitute_byte(byte_word[i]);
	}

	// Circular left shift
	circular_left_shift(g_return_word);
	
    return g_return_word;
}


// Get round key
byte *get_round_key(byte *key_bytes, unsigned char round_number) {
    byte *round_key = new byte[16];
	byte *transpose_key = new byte[16];

	// Transpose key to work with rows instead of columns
	for (unsigned int i = 0; i < 4; i++) {
        for (unsigned int j = 0; j < 4; j++) {
            transpose_key[i*4 + j] = key_bytes[j*4 + i];
        }
    }

	// Perform g function on word 3
	byte *word_zero = g_function(&transpose_key[12]);

	// Add round constant
	add_round_constant(word_zero, round_number);

	// XOR with word zero
	for (unsigned int i = 0; i < 4; i++) {
		word_zero[i] = word_zero[i] ^ transpose_key[i];
	}

	// Copy word zero to round key
	for (unsigned int i = 0; i < 4; i++) {
		round_key[i] = word_zero[i];
	}

	// Calculate words 1, 2, & 3
	for(unsigned int i = 0; i < 4; i++) {
		round_key[i + 4] = transpose_key[i + 4] ^ round_key[i];
		round_key[i + 8] = transpose_key[i + 8] ^ round_key[i + 4];
		round_key[i + 12] = transpose_key[i + 12] ^ round_key[i + 8];
	}

	// Transpose to return key to normal
	for (unsigned int i = 0; i < 4; i++) {
        for (unsigned int j = 0; j < 4; j++) {
            transpose_key[i*4 + j] = round_key[j*4 + i];
        }
    }

	delete word_zero;
	delete round_key;
	delete key_bytes;

	return transpose_key;
}

