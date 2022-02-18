#include "aes_128_common.h"

#ifndef AES_128_KEY_EXPANSION_H
#define AES_128_KEY_EXPANSION_H

// Inverse sub box lookup table
// REF: adapted from https://github.com/ceceww/aes/blob/master/structures.h
const byte rcon_table[11] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

void circular_left_shift(byte *byte_word);

void add_round_constant(byte *byte_word);

byte *g_function(byte *byte_word);

byte *get_round_key(byte *key_bytes, unsigned char round_number);

#endif //AES_128_KEY_EXPANSION_H
