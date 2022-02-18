#include "../include/aes_128_decrypt.h"
#include "../include/aes_128_key_expansion.h"

// Decryption function
byte *decrypt_aes_128(byte *ciphertext, byte *key) {
    byte *state = new byte[16];
    byte *round_key = new byte[16];
    byte *expanded_key = new byte[176];

    // Copy ciphertext to state
    for (unsigned int i = 0; i < 16; i++){
        state[i] = ciphertext[i];
    }

    // Copy key to expanded key and transpose
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            expanded_key[i*4 + j] = key[j*4 + i];
        }
    }

    // Copy first 16 bytes of extended key to round_key
    for (unsigned int i = 0; i < 16; i++){
        round_key[i] = expanded_key[i];
    }

    // Perform key expansion and store all round keys in expanded_key
    for (int i = 1; i < 11; i++) {
        round_key = get_round_key(round_key, i);
        for(unsigned int j = 0; j < 16; j++) {
            expanded_key[16*i + j] = round_key[j];
        }
	}

    // Initial round key
    round_key = &expanded_key[160];
    add_round_key(round_key, state);
    
    // Rounds 1-9
    for (unsigned int i = 1; i < 10; i++) {
	    inverse_shift_rows(state);
        inverse_substitute_bytes(state);
        round_key = &expanded_key[160 - i*16];
		add_round_key(round_key, state);
	    inverse_mix_columns(state);
    }

    // Final round
    inverse_shift_rows(state);	
    inverse_substitute_bytes(state);
    add_round_key(expanded_key, state);

    return state;
}

// IS-box ( Inverse substitute a single byte )
byte inverse_substitute_byte(byte byte_to_substitute) {
    byte inverse_byte = inverse_sub_table[byte_to_substitute];
    return inverse_byte;
}

// Inverse substitute the bytes of the state array
void inverse_substitute_bytes(byte *byte_array) {
     for (int x = 0; x < 16; x++) {
        byte_array[x] = inverse_substitute_byte(byte_array[x]);
    }
}

// Inverse Shift rows
void inverse_shift_rows(byte *byte_array) {
    byte *temp = new byte[16];

    // Row 1
    temp[0] = byte_array[0];
	temp[1] = byte_array[1];
	temp[2] = byte_array[2];
	temp[3] = byte_array[3];

	// Row 2
	temp[5] = byte_array[4];
	temp[6] = byte_array[5];
	temp[7] = byte_array[6];
	temp[4] = byte_array[7];

	// Row 3
	temp[10] = byte_array[8];
	temp[11] = byte_array[9];
	temp[8] = byte_array[10];
	temp[9] = byte_array[11];

	// Row 4
	temp[15] = byte_array[12];
	temp[12] = byte_array[13];
	temp[13] = byte_array[14];
	temp[14] = byte_array[15];

	for (int x = 0; x < 16; x++) {
		byte_array[x] = temp[x];
	}
}

// Inverse Mix Columns
void inverse_mix_columns(byte *byte_array) {
    byte *temp = new byte[16];
    
    for (unsigned int i = 0; i < 4; i++) {
		temp[i] = gf_mul_14[byte_array[i]] ^ gf_mul_11[byte_array[i+4]] ^ gf_mul_13[byte_array[i+8]] ^ gf_mul_9[byte_array[i+12]];
        temp[i+4] = gf_mul_9[byte_array[i]] ^ gf_mul_14[byte_array[i+4]] ^ gf_mul_11[byte_array[i+8]] ^ gf_mul_13[byte_array[i+12]];
        temp[i+8] = gf_mul_13[byte_array[i]] ^  gf_mul_9[byte_array[i+4]] ^ gf_mul_14[byte_array[i+8]] ^ gf_mul_11[byte_array[i+12]];
        temp[i+12] = gf_mul_11[byte_array[i]] ^ gf_mul_13[byte_array[i+4]] ^  gf_mul_9[byte_array[i+8]] ^ gf_mul_14[byte_array[i+12]];
	}

	for (int x = 0; x < 16; x++) {
		byte_array[x] = temp[x];
	}
}
